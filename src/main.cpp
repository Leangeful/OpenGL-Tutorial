#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

int windowWidth = 800;
int windowHeight = 600;
const std::string windowTitle = "OpenGL Window";

SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

void initializeProgram();
void mainLoop();
void cleanUp();

int main() {
  initializeProgram();

  mainLoop();

  cleanUp();

  std::cout << "Hello" << std::endl;
  return 0;
}

void initializeProgram() {
  int err = SDL_Init(SDL_INIT_VIDEO);
  if (err < 0) {
    std::cout << "ERROR::SDL::INIT::VIDEO " << err << std::endl;
    exit(err);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (window == nullptr) {
    std::cout << "ERROR::SDL::INIT::WINDOW" << std::endl;
    cleanUp();
    exit(-1);
  }

  glContext = SDL_GL_CreateContext(window);

  if (!glContext) {
    const char* err = SDL_GetError();
    std::cout << "ERROR::SDL::INIT::CONTEXT" << std::endl << err << std::endl;
    cleanUp();
    exit(-1);
  }
};

void mainLoop() {
  while (true) {
    char c;
    std::cin >> c;
  }
};

void cleanUp() { SDL_Quit(); };