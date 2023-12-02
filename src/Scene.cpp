#include "Scene.hpp"
#include <glad/glad.h>
Scene::Scene() {}

void Scene::draw() {
  for (SpatialObject object : spatialObjects) {
    object.draw();
  }
}

void Scene::addObject(SpatialObject obj) {
  if (!obj.shader) obj.shader = shader;
  spatialObjects.push_back(obj);
}
