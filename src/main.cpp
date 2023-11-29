#define SDL_MAIN_HANDLED

#include "init.hpp"
#include <vector>

int windowWidth = 800;
int windowHeight = 600;
const std::string windowTitle = "OpenGL Window";

bool shouldQuit = false;

SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

GLuint VAO;
GLuint VBO;
GLuint shaderProgram;

void specifyVertices();
void createGraphicsPipeline();
void mainLoop();
void handleInput();
void preDraw();
void draw();
void cleanUp();
void printOpenGLVersionInfo();

int main() {
  window = initWindow(windowTitle, windowWidth, windowHeight);
  glContext = initGL(window);

  printOpenGLVersionInfo();

  specifyVertices();

  createGraphicsPipeline();

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

void specifyVertices() {
  const std::vector<GLfloat> triangleVerts{
      -0.8f, -0.8f, .0f,  //  v1
      0.8f,  -0.8f, .0f,  //  v2
      0.0f,  0.8f,  .0f   //  v3

  };

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangleVerts.size(),
               triangleVerts.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
};

void createGraphicsPipeline(){};

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

void cleanUp() {
  SDL_DestroyWindow(window);
  SDL_Quit();
};

void printOpenGLVersionInfo() {
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
}