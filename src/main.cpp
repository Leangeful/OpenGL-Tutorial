#define SDL_MAIN_HANDLED
#define BUFFER_OFFSET(i) ((char*)NULL + (i))

#include "init.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <filesystem>

int windowWidth = 500;
int windowHeight = 500;
const std::string windowTitle = "OpenGL Window";

bool shouldQuit = false;
bool wireframeMode = false;

SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint shaderProgram;

const GLuint posAttribLen = 3;
const GLuint colAttribLen = 4;
const GLuint attribStride = posAttribLen + colAttribLen;

struct vertex {
  GLfloat posX, posY, posZ;
  GLfloat colR, colG, colB, colA;
};

std::vector<vertex> objectVerts{
    {-.2f, .4f, .0f, 0.38f, 0.71f, 0.71f, 1.0f},  //  v0
    {-.2f, .0f, .0f, 0.71f, 0.54f, 0.38f, 1.0f},  //  v1
    {.2f, .4f, .0f, 0.71f, 0.38f, 0.63f, 1.0f},   //  v2
    {.2f, .0f, .0f, 0.38f, 0.71f, 0.71f, 1.0f},   //  v3
    {.4f, .4f, .0f, 0.71f, 0.54f, 0.38f, 1.0f},   //  v4
    {.4f, .0f, .0f, 0.71f, 0.38f, 0.63f, 1.0f},   //  v5
};

const std::vector<GLuint> objectIdxs{
    0, 1, 2,  // first triangle
    1, 2, 3,  // second triangle
    2, 3, 4,  // third triangle
    3, 4, 5,  // fourth triangle
              // 3, 0, 2,  // random triangle

};

void specifyVertices();
void createGraphicsPipeline();
void mainLoop();
void handleInput();
void preDraw();
void draw();
void cleanUp();
void printOpenGLVersionInfo();
std::string loadShaderFile(std::string filePath);

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
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * objectVerts.size(),
               objectVerts.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * objectIdxs.size(),
               objectIdxs.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, posAttribLen, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        BUFFER_OFFSET(0));
  glVertexAttribPointer(1, colAttribLen, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        BUFFER_OFFSET(sizeof(GLfloat) * posAttribLen));

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

GLuint compileShader(GLuint type, const GLchar* source) {
  GLuint shader = glCreateShader(type);

  std::string typeString =
      type == GL_VERTEX_SHADER ? "GL_VERTEX_SHADER" : "GL_FAGMENT_SHADER";

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint shaderCompiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

  if (!shaderCompiled) {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetShaderInfoLog(shader, 1024, &log_length, message);

    std::cout << "ERROR COMPILING SHADER" << std::endl
              << typeString << std::endl
              << message << std::endl;
  }
  return shader;
}

GLuint createShaderProgram(std::string& vertexShaderSource,
                           std::string& fragmentShaderSource) {
  const GLchar* vSource = vertexShaderSource.c_str();
  const GLchar* fSource = fragmentShaderSource.c_str();

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fSource);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint programLinked;
  glGetProgramiv(program, GL_LINK_STATUS, &programLinked);

  if (!programLinked) {
    GLsizei logLength = 0;
    GLchar message[1024];
    glGetProgramInfoLog(program, 1024, &logLength, message);
    std::cout << "ERROR SHADER PROGRAM LINKING" << std::endl
              << message << std::endl;
  }

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

void createGraphicsPipeline() {
  std::string vertexShaderSource = loadShaderFile(".\\shaders\\basic.vert");

  std::string fragmentShaderSource = loadShaderFile(".\\shaders\\basic.frag");

  shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
};

void handleInput() {
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

void preDraw() {
  // glDisable(GL_DEPTH_TEST);
  // glDisable(GL_CULL_FACE);

  glViewport(0, 0, windowWidth, windowHeight);

  glClearColor(0.09, 0.10, 0.11, 1.0f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
};
void draw() {
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, objectIdxs.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glUseProgram(0);
};

void cleanUp() {
  std::cout << "CleanUp" << std::endl;
  SDL_DestroyWindow(window);
  SDL_Quit();
};

void printOpenGLVersionInfo() {
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
            << std::endl;
}

std::string loadShaderFile(std::string filePath) {
  std::ifstream sourceFile(filePath);
  std::string source = "";
  std::string tmp;

  if (sourceFile.is_open()) {
    while (std::getline(sourceFile, tmp)) {
      source += tmp + '\n';
    }
    sourceFile.close();
  } else {
    std::cerr << "ERROR LOADING SOURCE" << std::endl
              << std::strerror(errno) << std::endl;
  }

  return source;
}