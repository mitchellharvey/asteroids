#include "engine/Image.h"
#include "engine/Logger.h"

#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <cassert>
#include <mutex>

namespace {
    using namespace thirstyfish;
    std::unordered_map<AssetId, const Image * const> _images;
    std::mutex _mutex;
}

namespace thirstyfish {
const Image * const Image::get(AssetId id) {

    std::lock_guard<std::mutex> guard(_mutex);

    auto find = _images.find(id);
    if (find != _images.end()) {
        return find->second;
    }
    return nullptr;
}

Image::Image(const std::string& filePath) :
Asset(),
_filePath(filePath),
_loadedSurface(nullptr) {

    std::lock_guard<std::mutex> guard(_mutex);

    auto result = _images.emplace(_id, this);

    assert(result.second);
}

Image::Image(const Image& o) : 
Image(o._filePath)
{
    if (o.loaded()) {
        load();
    }
}

Image& Image::operator=(const Image& o) {
    unload();
    _filePath = o._filePath;
    if (o.loaded()) {
        load();
    }
}

Image::~Image() {
    unload();

    {
        std::lock_guard<std::mutex> guard(_mutex);
        _images.erase(_id);
    }
}

bool Image::load() {
    Logger::info("Creating SDL Surface for image: " + _filePath);

    if ( !loaded() && !(_loadedSurface = IMG_Load(_filePath.c_str())) ) {
        Logger::error("Failed to create SDL Surface for image: " + _filePath);
        return false;
    }

    return true;
}

void Image::unload() {
    if (loaded()) {
        Logger::info("Destroying SDL Surface for image: " + _filePath);
        SDL_FreeSurface(_loadedSurface);
        _loadedSurface = nullptr;
    }
}

bool Image::loaded() const {
    return _loadedSurface != nullptr;
}

std::string Image::filePath() const {
    return _filePath;
}

int Image::width() const {
    return loaded() ? _loadedSurface->w : 0;
}

int Image::height() const {
    return loaded() ? _loadedSurface->h : 0;
}

glm::ivec2 Image::size() const {
    return glm::ivec2(width(), height());
}

SDL_Texture* Image::createTexture(SDL_Renderer* renderer) const {
    SDL_Texture* texture = nullptr;
    if (loaded()) {
        texture = SDL_CreateTextureFromSurface(renderer, _loadedSurface);
        if (!texture) {
            Logger::error("Failed to create SDL Texture from surface for image: " + _filePath);
        }
    } else {
        Logger::error("Attempted to create texture from unloaded image: " + _filePath);
    }

    return texture;
}

}

