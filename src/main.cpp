#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

int windowWidth = 800;
int windowHeight = 600;

SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

void initializeProgram() {
  int err = SDL_Init(SDL_INIT_VIDEO);
  if (err < 0) {
    std::cout << "ERROR::SDL::INIT::VIDEO " << err << std::endl;
    cleanUp();
    exit(err);
  }
};

void mainLoop(){};

void cleanUp() { SDL_Quit(); };

int main() {
  initializeProgram();

  mainLoop();

  cleanUp();

  std::cout << "Hello" << std::endl;
  return 0;
}