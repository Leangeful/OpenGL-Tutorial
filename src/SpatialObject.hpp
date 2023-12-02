#ifndef SPATIALOBJECT_HPP
#define SPATIALOBJECT_HPP

#include <vector>
#include <glad/glad.h>
#include "types.hpp"
#include "Shader.hpp"

class SpatialObject {
 private:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  std::vector<vertex> verts;
  std::vector<GLuint> idxs;

 public:
  // GLuint shaderProgram = 0;
  Shader* shader = nullptr;
  GLuint primitiveMode = GL_TRIANGLES;

  SpatialObject();
  SpatialObject(std::vector<vertex> objectVerts,
                std::vector<GLuint> objectIdxs);

  void specifyVertices();
  void draw();
};

#endif /* SPATIALOBJECT_HPP */
