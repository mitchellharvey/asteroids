

#include "engine/System.h"
#include "engine/Window.h"
#include "engine/Logger.h"
#include "engine/Image.h"

#include <SDL2/SDL.h>

using namespace thirstyfish;

int main(int argc, char** argv) {

    Logger::logLevel(Logger::Level::DEBUG);

    if (!System::init()) {
        Logger::error("Failure during system initialization.  Exiting");
        return 1;
    }

    Window w("Asteroids!", glm::vec2(1920, 1080));

    Image ship("./assets/images/ship.png");

    Logger::info("Starting main loop");
    bool running = true;
    while(running) {

        // Process events
        System::processEvents([&running](const SDL_Event& event) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        });

        // Run Game Ticks
        
        // Render Scene
    }

    Logger::info("Window closed exiting application");

    return 0;
}

