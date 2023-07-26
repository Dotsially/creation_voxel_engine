#include "window.h"
#include <iostream>


Window::Window(int width, int height, std::string title){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        std::cout << "SDL could not be initialized" << std::endl;
        quit = true;
    }
    SDL_GL_LoadLibrary(NULL);
    // Request an OpenGL 4.6 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(window == NULL){
        std::cout << "Failed to create window" << std::endl;
        quit = true;
    } 

    this->glContext = SDL_GL_CreateContext(window);  
    if (glContext == NULL){
        std::cout << "Failed to create OpenGL context" << std::endl;
        quit = true;
    }  

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Failed to load OpenGL" << std::endl;
        quit = true;
    }

    SDL_GL_SetSwapInterval(0);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    glViewport(0,0,1280,720);
}

Window::~Window(){
    SDL_DestroyWindow( this->window );
    SDL_Quit();
}

bool Window::WindowShouldClose(){
    return quit;
}

void Window::PollEvents(){
    SDL_PollEvent(&e);
}

void Window::SwapBuffers(){
    SDL_GL_SwapWindow(window);
}

SDL_Event Window::GetEvents(){
    return e;
}

void Window::Quit(){
    quit = true;
}