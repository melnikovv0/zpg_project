// Scene.h
#pragma once
#include <vector>
#include "DrawableObject.h"

class Model;
class ShaderProgram;

class Scene {
public:
    DrawableObject& add(Model* model, ShaderProgram* program);
    void update(float dt);
    void render() const;
    void clear();

private:
    std::vector<DrawableObject> objects;
};
