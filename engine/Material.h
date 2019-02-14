#pragma once

#include "engine/Types.h"

#include <SDL2/SDL.h>

namespace thirstyfish {
struct Material {
    Material() = default;
    Material(const Material&) = default;

    AssetId image = NONE;
    SDL_Rect imageRect;
};
}

