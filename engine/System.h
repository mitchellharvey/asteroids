#pragma once

#include <functional>

#include <SDL2/SDL.h>

namespace thirstyfish {
class System {
public:
    static bool init();
    static void processEvents(std::function<void(const SDL_Event& event)> onEvent);

    System() = delete;
    ~System() = delete;
    System(const System&) = delete;
    System& operator=(const System&) = delete;
};
}

