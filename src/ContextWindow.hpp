#ifndef CONTEXTWINDOW_HPP
#define CONTEXTWINDOW_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>

class ContextWindow {
 private:
  SDL_Window* initWindow(const std::string windowTitle, int windowWidth,
                         int windowHeight);

  SDL_GLContext initGL(SDL_Window* window);

 public:
  SDL_Window* window = nullptr;
  SDL_GLContext context = nullptr;
  ContextWindow(const std::string windowTitle, int windowWidth,
                int windowHeight);
  ~ContextWindow();
};
#endif