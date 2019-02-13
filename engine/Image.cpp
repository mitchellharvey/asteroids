#include "engine/Image.h"
#include "engine/Logger.h"

#include <SDL2/SDL_image.h>

namespace thirstyfish {
Image::Image(const std::string& filePath) :
Asset(),
_filePath(filePath),
_loadedSurface(nullptr) {

    Logger::info("Creating SDL Surface for image: " + _filePath);

    if ( !(_loadedSurface = IMG_Load(_filePath.c_str())) ) {
        Logger::error("Failed to create SDL Surface for image: " + _filePath);
    }
}

Image::~Image() {
    if (_loadedSurface) {
        Logger::info("Destroying SDL Surface for image: " + _filePath);
        SDL_FreeSurface(_loadedSurface);
        _loadedSurface = nullptr;
    }
}
}

