#pragma once
#include "Transformation.h"
#include <vector>
#include <memory>


class CompositeTransform : public Transformation {
public:
    void add(const std::shared_ptr<Transformation>& t);//Přidat „detail“
    void clear();

    glm::mat4 matrix() const override; //vynásobí matice všech svých podřízených „částí“!
    void update(float dt) override;

private:
    std::vector<std::shared_ptr<Transformation>> children; //ukládá ukazatele na všechny podřízené transformace
};