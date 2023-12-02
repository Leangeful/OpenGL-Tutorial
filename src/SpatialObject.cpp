#include <SpatialObject.hpp>

SpatialObject::SpatialObject() {}

SpatialObject::SpatialObject(std::vector<vertex> objectVerts,
                             std::vector<GLuint> objectIdxs) {
  verts = objectVerts;
  idxs = objectIdxs;
  specifyVertices();
}

void SpatialObject::draw() {
  shader->use();
  shader->setFloat("xOffset", 0.5);
  glBindVertexArray(VAO);
  glDrawElements(primitiveMode, idxs.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glUseProgram(0);
}

void SpatialObject::specifyVertices() {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * verts.size(), verts.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * idxs.size(),
               idxs.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        BUFFER_OFFSET(0));
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex),
                        BUFFER_OFFSET(sizeof(GLfloat) * 3));

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};