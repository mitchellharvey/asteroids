#include "engine/Sprite.h"
#include "engine/Logger.h"
#include "engine/Image.h"

#include <glm/trigonometric.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

namespace thirstyfish {

glm::vec2 Sprite::localYAxis() const {
    glm::vec2 worldUp(0.0f, -1.0f);
    return glm::normalize(glm::rotate(worldUp, glm::radians(rotation)));
}

glm::vec2 Sprite::localXAxis() const {
    glm::vec2 worldRight(1.0f, 0.0f);
    return glm::normalize(glm::rotate(worldRight, glm::radians(rotation)));
}
}

