#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <string>
static std::string defaultVertPath = ".\\shaders\\basic.vert";
static std::string defaultFragPath = ".\\shaders\\basic.frag";

class GraphicsPipeline {
 private:
  SDL_Window* window = nullptr;
  SDL_GLContext context = nullptr;
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