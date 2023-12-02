#include "GraphicsPipeline.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

GLuint GraphicsPipeline::compileShader(GLuint type, const GLchar* source) {
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

GraphicsPipeline::GraphicsPipeline() {
  if (SDL_GL_GetCurrentContext()) {
    createGraphicsPipeline(defaultVertPath, defaultFragPath);
  }
}

GraphicsPipeline::GraphicsPipeline(std::string& vertPath,
                                   std::string& fragPath) {
  createGraphicsPipeline(vertPath, fragPath);
}

void GraphicsPipeline::createGraphicsPipeline(std::string& vertexShaderPath,
                                              std::string& fragmentShaderPath) {
  std::string vertexShaderSource = loadShaderFile(vertexShaderPath);
  std::string fragmentShaderSource = loadShaderFile(fragmentShaderPath);

  const GLchar* vSource = vertexShaderSource.c_str();
  const GLchar* fSource = fragmentShaderSource.c_str();

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fSource);

  program = glCreateProgram();
  // GLuint program =
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
}

std::string GraphicsPipeline::loadShaderFile(std::string& filePath) {
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