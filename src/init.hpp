#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <iostream>

SDL_Window* initWindow(const std::string windowTitle, int windowWidth,
                       int windowHeight);

SDL_GLContext initGL(SDL_Window* window);
