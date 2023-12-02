#include "GraphicsPipeline.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

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

GLuint createGraphicsPipeline(std::string& vertexShaderPath,
                              std::string& fragmentShaderPath) {
  std::string vertexShaderSource = loadShaderFile(vertexShaderPath);
  std::string fragmentShaderSource = loadShaderFile(fragmentShaderPath);

  const GLchar* vSource = vertexShaderSource.c_str();
  const GLchar* fSource = fragmentShaderSource.c_str();

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fSource);

  GLuint shaderProgram = glCreateProgram();
  // GLuint program =
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  GLint programLinked;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programLinked);

  if (!programLinked) {
    GLsizei logLength = 0;
    GLchar message[1024];
    glGetProgramInfoLog(shaderProgram, 1024, &logLength, message);
    std::cout << "ERROR SHADER PROGRAM LINKING" << std::endl
              << message << std::endl;
  }

  glDetachShader(shaderProgram, vertexShader);
  glDetachShader(shaderProgram, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

std::string loadShaderFile(std::string& filePath) {
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