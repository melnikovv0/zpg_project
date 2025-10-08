#pragma once
#include "Transformation.h"
#include <vector>
#include <memory>

// Композит: хранит набор дочерних трансформаций и перемножает их по порядку добавления
class CompositeTransform : public Transformation {
public:
    void add(const std::shared_ptr<Transformation>& t);
    void clear();

    glm::mat4 matrix() const override;
    void update(float dt) override;

private:
    std::vector<std::shared_ptr<Transformation>> children;
};