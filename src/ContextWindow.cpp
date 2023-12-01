#include "ContextWindow.hpp"
#include <iostream>

ContextWindow::ContextWindow(const std::string windowTitle, int windowWidth,
                             int windowHeight) {
  window = initWindow(windowTitle, windowWidth, windowHeight);
}

ContextWindow::~ContextWindow() {}

SDL_Window* ContextWindow::initWindow(const std::string windowTitle,
                                      int windowWidth, int windowHeight) {
  SDL_Window* window = nullptr;
  int err = SDL_Init(SDL_INIT_VIDEO);
  if (err < 0) {
    std::cout << "ERROR::SDL::INIT::VIDEO " << err << std::endl;
    exit(err);
  }

  window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (window == nullptr) {
    std::cout << "ERROR::SDL::INIT::WINDOW" << std::endl;
    exit(-1);
  }

  return window;
};

SDL_GLContext ContextWindow::initGL(SDL_Window* window) {
  SDL_GLContext glContext = nullptr;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  glContext = SDL_GL_CreateContext(window);

  if (!glContext) {
    const char* err = SDL_GetError();
    std::cout << "ERROR::SDL::INIT::CONTEXT" << std::endl << err << std::endl;
    exit(-1);
  }

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    std::cout << "ERROR::GLAD::INIT::GL" << std::endl;
    exit(-1);
  }

  return glContext;
}
