#define SDL_MAIN_HANDLED

#include "init.hpp"
#include <vector>
#include <string>

int windowWidth = 500;
int windowHeight = 500;
const std::string windowTitle = "OpenGL Window";

bool shouldQuit = false;

SDL_Window* window = nullptr;
SDL_GLContext glContext = nullptr;

GLuint VAO;
GLuint VBO;
GLuint shaderProgram;

const std::vector<GLfloat> triangleVerts{
    -.2f, .4f, .0f,   //  v0
    -.2f, .0f, .0f,   //  v1
    .2f,  .4f, .0f,   //  v2
    .2f,  .0f, .0f,   //  v3
    .4f,  .4f, -.4f,  //  v4
    .4f,  .0f, -.4f,  //  v5

};

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

GLuint createShaderProgram(const GLchar* vertexShaderSource,
                           const GLchar* fragmentShaderSource) {
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);

  GLuint fragmentShader =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

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

    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          shouldQuit = true;
          break;

        case SDLK_a:
          std::cout << "Move Left Repeat: " << std::to_string(e.key.repeat)
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
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
};
void draw() {
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, triangleVerts.size() / 3);
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
}