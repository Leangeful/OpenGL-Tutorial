#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>
#include "Scene.hpp"
#include "GraphicsPipeline.hpp"

class Engine {
 private:
  SDL_Window* initWindow();
  SDL_GLContext initGL(SDL_Window* window);
  void preDraw();

  bool shouldQuit = false;

 public:
  Engine();
  Engine(std::string title, int width, int height);
  ~Engine();

  void mainLoop();
  void handleInput();
  void printOpenGLVersionInfo();
  void cleanUp();

  GLuint windowWidth = 500;
  GLuint windowHeight = 500;
  std::string windowTitle = "OpenGL Window";
  bool wireframeMode = false;

  SDL_Window* window = nullptr;
  SDL_GLContext context = nullptr;
  Scene* activeScene = nullptr;

  // GraphicsPipeline defaultGP;
  GLuint defaultProgram;
};
#endif