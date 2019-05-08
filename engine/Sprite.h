#pragma once

#include "engine/Material.h"

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace thirstyfish {
struct Sprite {

    Sprite() = default;
    Sprite(const Sprite&) = default;

    Material material;
    glm::vec2 position;
    glm::ivec2 size;
};
}

