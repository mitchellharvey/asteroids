#include "engine/System.h"
#include "engine/Logger.h"

#include <SDL2/SDL.h>

// TODO: 
// Add runtime checks to ensure these functions are always called on the same thread

namespace thirstyfish {

bool System::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::error("Failed to initialize SDL");
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
