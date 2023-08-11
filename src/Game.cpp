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
#include "window.h"
#include "texture.h"
#include "shader.h"
#include "block_handler.h"
#include "world.h"
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
        if(j % 2 == 0){
            for(u32 i : VerticesList::indicesCube[0]){
                iBuffer.push_back(i + (j*4));
            }
        }
        else{
            for(u32 i : VerticesList::indicesCube[1]){
                iBuffer.push_back(i + (j*4));
            }
        }
        
    }
    Window gameWindow = Window(1280, 720, "World");
    
    //opengl stuff
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera = Camera(CAMERA_FREECAM, glm::vec3(0,5,5));
    Texture texture = Texture("tilemap.png");
    Texture texture2 = Texture("selection.png");
    Shader shader = Shader("chunk_vertex.glsl", "chunk_fragment.glsl");
    Shader shaderBlock = Shader("vertex_selection.glsl", "fragment_selection.glsl");
    World world;
    BlockHandler blockHandler;
    std::cout << "world created" << std::endl;

    Mesh selectionMesh;

    selectionMesh.InitializeMesh(GL_STATIC_DRAW, vBuffer.data(), vBuffer.size(), iBuffer.data(), iBuffer.size());

    perspective = camera.GetProjectMatrix();
    
    
    while (!gameWindow.WindowShouldClose())
    {
        gameWindow.PollEvents();
        const u8* keystate = SDL_GetKeyboardState(NULL);

        InputHandler(&gameWindow, keystate);
        camera.Update(keystate);
        blockHandler.Update(&camera, &world, keystate);

        transform2 = glm::translate(blockHandler.GetBlock());
        transform2 = glm::scale(transform2, glm::vec3(1.02f,1.02f,1.02f));

        view = camera.GetViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        texture.ActivateTexture();
        shader.UseProgram();
        glUniformMatrix4fv(1,1, false, glm::value_ptr(perspective));
        glUniformMatrix4fv(2,1, false, glm::value_ptr(view));

        world.Draw(camera.GetPosition());

        if(blockHandler.IsSolid()){
            texture2.ActivateTexture();
            shaderBlock.UseProgram();
            glUniformMatrix4fv(1,1, false, glm::value_ptr(perspective));
            glUniformMatrix4fv(2,1, false, glm::value_ptr(view));
            selectionMesh.DrawMesh(iBuffer.size(), transform2);
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