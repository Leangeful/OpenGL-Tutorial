#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "SpatialObject.hpp"
class Scene {
 private:
  /* data */
 public:
  Scene(/* args */);
  ~Scene();
  void preDraw();
  void draw();

  std::vector<SpatialObject> spatialObjects;
};
#endif