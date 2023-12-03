#include <Texture.hpp>

Texture::Texture() {}
Texture::Texture(std::string& imagePath) {
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  int width, height, nrChannels;
  unsigned char* data =
      stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);

    if (generateMipmap) glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "ERROR LOADING TEXTURE" << std::endl
              << "Path: " << imagePath << std::endl;
  }

  stbi_image_free(data);
}
