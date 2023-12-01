#ifndef CORE_HPP
#define CORE_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>

class Core {
 private:
  SDL_Window* initWindow(const std::string windowTitle, int windowWidth,
                         int windowHeight);

  SDL_GLContext initGL(SDL_Window* window);

 public:
  SDL_Window* window = nullptr;
  SDL_GLContext context = nullptr;
  Core();
  Core(const std::string windowTitle, int windowWidth, int windowHeight);
  ~Core();
};
#endif