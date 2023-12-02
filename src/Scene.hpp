#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <SpatialObject.hpp>
#include <Shader.hpp>

class Scene {
 public:
  Shader* shader = nullptr;
  std::vector<SpatialObject> spatialObjects;

  Scene();
  void draw();
  void addObject(SpatialObject obj);
};
#endif