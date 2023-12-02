#define SDL_MAIN_HANDLED

#include <vector>
#include <iostream>

#include "Engine.hpp"
#include "SpatialObject.hpp"
#include "whereami.h"

// TODO "settings"
int windowWidth = 500;
int windowHeight = 500;
std::string windowTitle = "OpenGL Window";
std::string exeName = "build.exe";

std::string exePath = "";

std::string defaultVertPath = "shaders\\basic.vert";
std::string defaultFragPath = "shaders\\basic.frag";
std::string redFragPath = "shaders\\red.frag";

// TODO import objects from file
std::vector<vertex> objectVerts{
    {-.2f, .4f, .0f, 0.38f, 0.71f, 0.71f, 1.0f},  //  v0
    {-.2f, .0f, .0f, 0.71f, 0.54f, 0.38f, 1.0f},  //  v1
    {.2f, .4f, .0f, 0.71f, 0.38f, 0.63f, 1.0f},   //  v2
    {.2f, .0f, .0f, 0.38f, 0.71f, 0.71f, 1.0f},   //  v3
    {.4f, .4f, .0f, 0.71f, 0.54f, 0.38f, 1.0f},   //  v4
    {.4f, .0f, .0f, 0.71f, 0.38f, 0.63f, 1.0f},   //  v5
};

std::vector<GLuint> objectIdxs{
    0, 1, 2,  // first triangle
    1, 2, 3,  // second triangle
    2, 3, 4,  // third triangle
    3, 4, 5,  // fourth triangle
};

std::vector<vertex> object2{
    {.6f, .5f, .0f, 0.38f, 0.72f, 0.48f, 1.0f},   //  v0
    {1.0f, .5f, .0f, 0.38f, 0.72f, 0.48f, 1.0f},  //  v1
    {.8f, .8f, .0f, 0.0f, 0.72f, 0.48f, 1.0f},    //  v2
};

std::vector<GLuint> idxs2{
    0, 1, 2,  // first triangle
};

void getExePath() {
  int dirname_length = 512;
  int length = wai_getModulePath(NULL, 0, NULL);
  char* path = path = (char*)malloc(length + 1);
  wai_getModulePath(path, length, &dirname_length);
  path[length] = '\0';

  exePath = path;
  free(path);
  exePath = exePath.substr(0, exePath.size() - exeName.size());
}

void makeShaderPaths() {
  defaultVertPath = exePath + defaultVertPath;
  defaultFragPath = exePath + defaultFragPath;
  redFragPath = exePath + redFragPath;
}

int main() {
  getExePath();
  makeShaderPaths();

  std::cout << "Path: " << exePath << std::endl;
  Engine engine = Engine(windowTitle, windowWidth, windowHeight);

  engine.printOpenGLVersionInfo();

  Shader defaultShader(defaultVertPath, defaultFragPath);
  Shader redShader(defaultVertPath, redFragPath);

  Scene startScene;
  startScene.shader = &defaultShader;

  SpatialObject testThing(objectVerts, objectIdxs);
  SpatialObject triangle2(object2, idxs2);

  // triangle2.shaderProgram = redShaderProg;

  // testThing.primitiveMode = GL_TRIANGLE_FAN;

  startScene.addObject(testThing);
  startScene.addObject(triangle2);

  engine.activeScene = &startScene;

  engine.mainLoop();

  engine.cleanUp();

  return 0;
}
