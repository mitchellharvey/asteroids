#include "engine/System.h"
#include "engine/Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// TODO: 
// Add runtime checks to ensure these functions are always called on the same thread

namespace thirstyfish {

bool System::init() {
    Logger::info("Initialize SDL Video");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::error("Failed to initialize SDL Video");
        Logger::error(SDL_GetError());
        return false;
    }

    Logger::info("Initialize SDL Image");
    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) {
        Logger::error("Failed to initialize SLD Image");
        Logger::error(SDL_GetError());
        return false;
    }

    return true;
}

void System::processEvents(std::function<void(const SDL_Event& event)> onEvent) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        onEvent(e);
    }
}

}
