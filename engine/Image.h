#pragma once

#include "engine/Asset.h"

#include <string>
#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace thirstyfish {
class Image : public Asset {
public:
    Image(const std::string& filePath);
    virtual ~Image();

    Image(const Image& o);
    Image& operator=(const Image& o);

    static const Image * const get(AssetId id);

    bool load();
    void unload();

    bool loaded() const;
    std::string filePath() const;
    int width() const;
    int height() const;
    glm::ivec2 size() const;

    SDL_Texture* createTexture(SDL_Renderer* renderer) const;

private:
    std::string _filePath;
    SDL_Surface* _loadedSurface;
};
}



