#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <string>
#include <stb_image/stb_image.h>
#include <glad/glad.h>

class Texture {
 private:
  /* data */
 public:
  GLuint ID;
  std::string imagePath;
  bool generateMipmap = true;
  Texture();
  Texture(std::string& imagePath);
};

#endif