#include <Engine.hpp>
#include <iostream>

void Engine::mainLoop() {
  while (!shouldQuit) {
    handleInput();
    preDraw();
    activeScene->draw();

    SDL_GL_SwapWindow(window);
  }
}

Engine::Engine() {}
Engine::Engine(std::string title, int width, int height) {
  this->windowWidth = width;
  this->windowHeight = height;
  this->windowTitle = title;
  window = initWindow();
  context = initGL(window);
}

Engine::~Engine() {}

SDL_Window* Engine::initWindow() {
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

SDL_GLContext Engine::initGL(SDL_Window* window) {
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

void Engine::cleanUp() {
  std::cout << "CleanUp" << std::endl;
  SDL_DestroyWindow(window);
  SDL_Quit();
};

// TODO make inputhandler
void Engine::handleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) shouldQuit = true;

    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          shouldQuit = true;
          break;

        case SDLK_a:
          std::cout << "Move Left Repeat: " << std::to_string(e.key.repeat)
                    << std::endl;
          break;

        case SDLK_p:
          wireframeMode = !wireframeMode;
          std::cout << "wireframeMode: " << std::to_string(wireframeMode)
                    << std::endl;
          break;

        default:
          break;
      }
    }

    // if (e.type == SDL_WINDOWEVENT) {
    if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      // TODO Account for different types of window scaling
      // currently: stretch
      windowWidth = e.window.data1;
      windowHeight = e.window.data2;
    }
    //}
  }
}
void Engine::preDraw() {
  glViewport(0, 0, windowWidth, windowHeight);
  glClearColor(0.09, 0.10, 0.11, 1.0f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
}

void Engine::printOpenGLVersionInfo() {
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
}