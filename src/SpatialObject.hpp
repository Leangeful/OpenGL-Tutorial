#ifndef SPATIALOBJECT_HPP
#define SPATIALOBJECT_HPP

#include <vector>
#include <glad/glad.h>
#include <types.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

class SpatialObject {
 private:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  std::vector<vertex> verts;
  std::vector<GLuint> idxs;

 public:
  Shader* shader = nullptr;
  Texture* texture = nullptr;
  GLuint primitiveMode = GL_TRIANGLES;
  // TODO create list(s) for shader attributes

  SpatialObject();
  SpatialObject(std::vector<vertex> objectVerts,
                std::vector<GLuint> objectIdxs);

  void specifyVertices();
  void draw();
};

#endif /* SPATIALOBJECT_HPP */
