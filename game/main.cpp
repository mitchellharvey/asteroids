#include <iostream>
#include <thread>
using namespace std;

#include <SDL2/SDL.h>

#include "engine/System.h"
#include "engine/Window.h"
#include "engine/Logger.h"

using namespace thirstyfish;

int main(int argc, char** argv) {

    Logger::logLevel(Logger::Level::DEBUG);

    if (!System::init()) {
        return 1;
    }

    Window w;

    Logger::info("Starting main loop");
    bool running = true;
    while(running) {
        System::processEvents([&running](const SDL_Event& event) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        });
    }

    Logger::info("Window closed exiting application");

    return 0;
}

