#include "Scene.hpp"
#include <glad/glad.h>
Scene::Scene() {}

Scene::~Scene() {}

void Scene::draw() {
  for (SpatialObject object : spatialObjects) {
    object.draw();
  }
}

void Scene::addObject(SpatialObject obj) {
  if (!obj.program) obj.program = program;
  spatialObjects.push_back(obj);
}
