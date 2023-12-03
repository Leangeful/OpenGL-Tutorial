#include <glad/glad.h>

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

struct vertex {
  GLfloat posX, posY, posZ;
  GLfloat colR, colG, colB, colA;
  GLfloat texU, texV;
};