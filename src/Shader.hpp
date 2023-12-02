#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

class Shader {
 private:
  GLuint compileShader(GLuint type, const GLchar* source);
  std::string loadShaderFile(std::string& filePath);

 public:
  GLuint ID = 0;

  Shader(std::string& vertexPath, std::string& fragmentPath);

  void use();
};

#endif
