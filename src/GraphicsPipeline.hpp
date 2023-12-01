#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <string>

class GraphicsPipeline {
 private:
  GLuint compileShader(GLuint type, const GLchar* source);
  std::string loadShaderFile(std::string& filePath);
  void createGraphicsPipeline(std::string& vertexShaderPath,
                              std::string& fragmentShaderPath);

 public:
  /* std::string vertexShaderPath;
  std::string fragmentShaderPath; */
  GLuint program = 0;

  GraphicsPipeline();
  GraphicsPipeline(std::string& vertexShaderPath,
                   std::string& fragmentShaderPath);
};

#endif /* GRAPHICSPIPELINE_HPP */