#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>
#include "Scene.hpp"

class Engine {
 private:
  SDL_Window* initWindow(const std::string windowTitle, int windowWidth,
                         int windowHeight);

  SDL_GLContext initGL(SDL_Window* window);

 public:
  Engine();
  Engine(const std::string windowTitle, int windowWidth, int windowHeight);
  ~Engine();
  SDL_Window* window = nullptr;
  SDL_GLContext context = nullptr;
  Scene* activeScene = nullptr;
};
#endif