#pragma once

#include "engine/Material.h"

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace thirstyfish {
struct Sprite {

    Sprite();
    Sprite(const Sprite&) = default;

    glm::vec2 localYAxis() const;
    glm::vec2 localXAxis() const;

    Material material;
    glm::vec2 position;
    glm::ivec2 size;

    float rotation = 0.0f;
};
}

