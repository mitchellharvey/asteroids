#pragma once

#include "engine/Material.h"

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace thirstyfish {
struct Sprite {

    Sprite() = default;
    Sprite(const Sprite&) = default;

    virtual void render(SDL_Renderer* renderer);

    Material material;
    glm::ivec2 position;
    glm::ivec2 size;
};
}

