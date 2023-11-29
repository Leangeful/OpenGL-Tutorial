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

GLuint createShaderProgram(const GLchar* vertexShaderSource,
                           const GLchar* fragmentShaderSource) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLint vertexCompiled;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompiled);

  if (!vertexCompiled) {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetShaderInfoLog(vertexShader, 1024, &log_length, message);

    std::cout << "ERROR VERTEX SHADER COMPILE" << std::endl
              << message << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  GLint fragmentCompiled;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompiled);

  if (!fragmentCompiled) {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetShaderInfoLog(fragmentShader, 1024, &log_length, message);

    std::cout << "ERROR FRAGMENT SHADER COMPILE" << std::endl
              << message << std::endl;
  }

  GLuint program = glCreateProgram();
  // glBindAttribLocation(program, 0, "position");
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

  return program;
}

void createGraphicsPipeline() {
  const GLchar* vertexShaderSource =
      "#version 460 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main(){\n"
      "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  const GLchar* fragmentShaderSource =
      "#version 460 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";

  shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
};

void handleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) shouldQuit = true;

    if (e.type == SDL_KEYDOWN)
      if (e.key.keysym.sym == SDLK_ESCAPE) shouldQuit = true;
  }
}

void preDraw() {
  glClearColor(0.09, 0.10, 0.11, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
};
void draw() {
  glUseProgram(shaderProgram);
  // glEnableVertexAttribArray(0);
  glBindVertexArray(VAO);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  // glDrawBuffer(VBO);
};

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