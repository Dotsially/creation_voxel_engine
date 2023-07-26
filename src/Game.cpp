#pragma once
#define SDL_MAIN_HANDLED
#define FNL_IMPL
#include "depedencies.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "render.h"
#include "shader.h"
#include "window.h"
#include "chunk.h"
#include "block_handler.h"
#include "camera.h"

void InputHandler(Window* gameWindow, const u8* keystate); 

glm::mat4 view;
glm::mat4 perspective;
glm::mat4 transform = glm::mat4(1.0);
glm::mat4 transform2 = glm::mat4(1.0);

int main(int argc, char* args[]){
    std::vector<f32> vBuffer;
    std::vector<u32> iBuffer;

    vBuffer.insert(vBuffer.begin(), VerticesList::verticesCube[0], VerticesList::verticesCube[0]+72);

    for(int j = 0; j < 6; j++){
    for(u32 i : VerticesList::indicesCube){
            iBuffer.push_back(i + (j*4));
    }
    }

    Window gameWindow = Window(1280, 720, "World");
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    Camera camera = Camera(CAMERA_FIRSTPERSON, glm::vec3(0,5,5));
    Shader shader = Shader("vertex.glsl", "fragment.glsl");
    Chunk chunk;
    BlockHandler blockHandler;

    chunk.CreateChunkData();
    chunk.CreateChunkMesh();

    u32 vbo2;
    u32 vao2;
    u32 ebo2;

    glGenBuffers(1, &vbo2);
    glGenBuffers(1, &ebo2);
    glGenVertexArrays(1, &vao2);

    glBindVertexArray(vao2);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, vBuffer.size()*sizeof(f32), vBuffer.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iBuffer.size()*sizeof(u32), iBuffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), 0);
    glEnableVertexAttribArray(0);

    perspective = camera.GetProjectMatrix();
    
    
    while (!gameWindow.WindowShouldClose())
    {
        gameWindow.PollEvents();
        const u8* keystate = SDL_GetKeyboardState(NULL);

        InputHandler(&gameWindow, keystate);
        camera.Update(keystate);
        blockHandler.Update(&camera, &chunk);

        transform2 = glm::translate(blockHandler.GetBlock());
        transform2 = glm::scale(transform2, glm::vec3(1.05f,1.05f,1.05f));

        view = camera.GetViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.UseProgram();
        glUniformMatrix4fv(1,1, false, glm::value_ptr(perspective));
        glUniformMatrix4fv(2,1, false, glm::value_ptr(view));

        chunk.Draw();

        if(blockHandler.IsSolid()){
            glBindVertexArray(vao2);

            glUniformMatrix4fv(0,1, false, glm::value_ptr(transform2));

            glDrawElements(GL_TRIANGLES, iBuffer.size(), GL_UNSIGNED_INT, 0);
        }

        gameWindow.SwapBuffers();
    }

    return 0;
}

void InputHandler(Window* gameWindow, const u8* keystate){
    SDL_Event e = gameWindow->GetEvents();
    if(e.type  == SDL_QUIT){
        gameWindow->Quit();
    }
    if(keystate[SDL_SCANCODE_ESCAPE]){
        gameWindow->Quit();    
    }
}