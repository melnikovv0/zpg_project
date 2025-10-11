
#include "CompositeTransform.h"

void CompositeTransform::add(const std::shared_ptr<Transformation>& t) {
    children.push_back(t);
}

void CompositeTransform::clear() {
    children.clear();
}

glm::mat4 CompositeTransform::matrix() const {
    glm::mat4 m(1.0f); // „prázdná“ transformace
    for (const auto& c : children) {
        m = c->matrix() * m; // Умножаем справа налево
    }
    return m;
}

void CompositeTransform::update(float dt) {
    for (const auto& c : children) c->update(dt);
}
