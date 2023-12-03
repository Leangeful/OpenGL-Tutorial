#define SDL_MAIN_HANDLED

#include <vector>
#include <iostream>

#include <Engine.hpp>
#include <SpatialObject.hpp>
#include <Texture.hpp>

#include <whereami.h>

// TODO "settings"
int windowWidth = 500;
int windowHeight = 500;
std::string windowTitle = "OpenGL Window";
std::string exeName = "build.exe";

std::string exePath = "";

std::string defaultVertPath = "shaders\\basic.vert";
std::string defaultFragPath = "shaders\\basic.frag";
std::string redFragPath = "shaders\\red.frag";
std::string redVertPath = "shaders\\red.vert";

std::string texPath = "textures\\test_text.jpg";

// TODO import objects from file
std::vector<vertex> rectVerts{
    // positions     //colors                   //UV
    {0.5f, 0.5f, 0.0f, 0.38f, 0.71f, 0.71f, 1.0f, 1.0f, 0.0f},   // top right
    {0.5f, -0.5f, 0.0f, 0.71f, 0.54f, 0.38f, 1.0f, 1.0f, 1.0f},  // bottom right
    {-0.5f, -0.5f, 0.0f, 0.71f, 0.38f, 0.63f, 1.0f, 0.0f, 1.0f},  // bottom left
    {-0.5f, 0.5f, 0.0f, 0.38f, 0.71f, 0.71f, 1.0f, 0.0f, 0.0f},   // top left
    //{.4f, .4f, .0f, 0.71f, 0.54f, 0.38f, 1.0f},   //  v4
    //{.4f, .0f, .0f, 0.71f, 0.38f, 0.63f, 1.0f},   //  v5
};

std::vector<GLuint> rectIdxs{
    0, 1, 3,  // first triangle
    1, 2, 3,  // second triangle
              // 2, 3, 4,  // third triangle
              // 3, 4, 5,  // fourth triangle
};

std::vector<vertex> object2{
    {-.2f, .5f, .0f, 0.38f, 0.72f, 0.48f, 1.0f},  //  v0
    {.2f, .5f, .0f, 0.38f, 0.72f, 0.48f, 1.0f},   //  v1
    {.0f, .8f, .0f, 0.0f, 0.72f, 0.48f, 1.0f},    //  v2
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

void makePaths() {
  defaultVertPath = exePath + defaultVertPath;
  defaultFragPath = exePath + defaultFragPath;
  redFragPath = exePath + redFragPath;
  redVertPath = exePath + redVertPath;
  texPath = exePath + texPath;
}

int main() {
  getExePath();
  makePaths();

  std::cout << "Path: " << exePath << std::endl;
  Engine engine = Engine(windowTitle, windowWidth, windowHeight);

  engine.printOpenGLVersionInfo();

  Shader defaultShader(defaultVertPath, defaultFragPath);
  Shader redShader(redVertPath, redFragPath);

  Scene startScene;
  startScene.shader = &defaultShader;

  SpatialObject rect(rectVerts, rectIdxs);

  Texture rectTex(texPath);

  rect.texture = &rectTex;

  SpatialObject triangle2(object2, idxs2);

  triangle2.shader = &redShader;

  // testThing.primitiveMode = GL_TRIANGLE_FAN;

  startScene.addObject(rect);
  startScene.addObject(triangle2);

  engine.activeScene = &startScene;

  engine.mainLoop();

  engine.cleanUp();

  return 0;
}
