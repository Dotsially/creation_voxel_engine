#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include <string>

class Window{
    private:
    SDL_Window* window = NULL;
    SDL_GLContext glContext = NULL;
    SDL_Event e;
    bool quit = false;

    public:
    Window(int width, int height, std::string title);
    ~Window();
    bool WindowShouldClose();
    void Quit();
    void PollEvents();
    void SwapBuffers();

    SDL_Event GetEvents();
};