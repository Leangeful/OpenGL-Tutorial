#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <iostream>
#include <string>

int windowWidth = 800;
int windowHeight = 600;
const std::string windowTitle = "OpenGL Window";

bool shouldQuit = false;

SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

void initializeProgram();
void mainLoop();
void handleInput();
void preDraw();
void draw();
void cleanUp();
void printOpenGLVersionInfo();

int main() {
  initializeProgram();

  mainLoop();

  cleanUp();

  return 0;
}

void mainLoop() {
  while (!shouldQuit) {
    handleInput();
    preDraw();
    draw();
    SDL_GL_SwapWindow(window);
  }
};

void handleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) shouldQuit = true;

    if (e.type == SDL_KEYDOWN)
      if (e.key.keysym.sym == SDLK_ESCAPE) shouldQuit = true;
  }
}

void preDraw(){};
void draw(){};

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
    exit(-1);
  }

  glContext = SDL_GL_CreateContext(window);

  if (!glContext) {
    const char* err = SDL_GetError();
    std::cout << "ERROR::SDL::INIT::CONTEXT" << std::endl << err << std::endl;
    cleanUp();
    exit(-1);
  }

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    std::cout << "ERROR::GLAD::INIT" << std::endl;
    cleanUp();
    exit(-1);
  }

  printOpenGLVersionInfo();
};

void cleanUp() {
  std::cout << "cleaning up" << std::endl;
  SDL_DestroyWindow(window);
  SDL_Quit();
};

void printOpenGLVersionInfo() {
  // const GLubyte* vendor = glGetString(GL_VENDOR);
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
}