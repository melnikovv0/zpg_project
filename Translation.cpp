#include "Translation.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Translation::matrix() const {
    glm::mat4 m(1.0f);
    return glm::translate(m, t);
}
