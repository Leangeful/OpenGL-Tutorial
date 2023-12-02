#ifndef SPATIALOBJECT_HPP
#define SPATIALOBJECT_HPP

#include <vector>
#include <glad/glad.h>
#include "types.hpp"

class SpatialObject {
 private:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  std::vector<vertex> verts;
  std::vector<GLuint> idxs;

 public:
  SpatialObject();
  SpatialObject(std::vector<vertex> objectVerts,
                std::vector<GLuint> objectIdxs);
  ~SpatialObject();

  void specifyVertices();

  void draw();

  GLuint shaderProgram = 0;
  GLuint primitiveMode = GL_TRIANGLES;
};

#endif /* SPATIALOBJECT_HPP */
