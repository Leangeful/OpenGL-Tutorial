#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "SpatialObject.hpp"

class Scene {
 public:
  Scene();
  ~Scene();

  void draw();
  void addObject(SpatialObject obj);

  GLuint program;
  std::vector<SpatialObject> spatialObjects;
};
#endif