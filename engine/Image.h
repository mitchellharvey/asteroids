#pragma once

#include "engine/Asset.h"

#include <string>
#include <SDL2/SDL.h>

namespace thirstyfish {
class Image : public Asset {
public:
    Image(const std::string& filePath);
    virtual ~Image();

    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

private:
    std::string _filePath;
    SDL_Surface* _loadedSurface;
};
}



