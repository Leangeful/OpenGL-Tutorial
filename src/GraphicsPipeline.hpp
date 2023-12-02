#ifndef GRAPHICSPIPELINE_HPP
#define GRAPHICSPIPELINE_HPP

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <string>

GLuint createGraphicsPipeline(std::string& vertexShaderPath,
                              std::string& fragmentShaderPath);

GLuint compileShader(GLuint type, const GLchar* source);
std::string loadShaderFile(std::string& filePath);

#endif /* GRAPHICSPIPELINE_HPP */