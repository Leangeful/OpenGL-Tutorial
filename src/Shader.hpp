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

  // utility uniform functions
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
};

#endif
