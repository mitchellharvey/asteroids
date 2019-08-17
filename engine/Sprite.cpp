#include "engine/Sprite.h"
#include "engine/Logger.h"
#include "engine/Image.h"

#include <glm/trigonometric.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

namespace thirstyfish {

Sprite::Sprite() :
position(0.0f, 0.0f),
size(0.0f, 0.0f)
{
}

SDL_Rect Sprite::bounds() const {
    static float anchors[][2] = {
        {0.0f, 0.0f},
        {-1.0f, 0.0f},
        {0.0f, -1.0f},
        {-1.0f, -1.0f},
        {-0.5f, -0.5f}
    };

    float x = position.x + (size.x * anchors[material.anchor][0]);
    float y = position.y + (size.y * anchors[material.anchor][1]);
    SDL_Rect result {static_cast<int>(x), static_cast<int>(y), size.x, size.y};
    return result;
}

glm::vec2 Sprite::localYAxis() const {
    glm::vec2 worldUp(0.0f, -1.0f);
    return glm::normalize(glm::rotate(worldUp, glm::radians(rotation)));
}

glm::vec2 Sprite::localXAxis() const {
    glm::vec2 worldRight(1.0f, 0.0f);
    return glm::normalize(glm::rotate(worldRight, glm::radians(rotation)));
}
}

