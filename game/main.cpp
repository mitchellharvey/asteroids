

#include "engine/System.h"
#include "engine/Window.h"
#include "engine/Logger.h"
#include "engine/String.h"

#include "Game.h"

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <cmath>

using namespace thirstyfish;

void checkSDLError() {

    const char* err = SDL_GetError();
    if (err[0] != 0) {
        Logger::error(fmt("SDL ERROR: {}",err));
        SDL_ClearError();
    }
}


int main(int argc, char** argv) {

    Logger::logLevel(Logger::Level::DEBUG);

    if (!System::init()) {
        Logger::error("Failure during system initialization.  Exiting");
        return 1;
    }

    std::string windowTitle = "Asteroids!";
    Window w(windowTitle, glm::vec2(1920, 1080));
    checkSDLError();

    Game game(&w);

    Logger::info("Starting main loop");
    bool running = true;

    const float UPDATES_PER_SECOND = 60.0f;
    const float FRAMES_PER_SECOND = 144.0f;

    const float TICKS_PER_UPDATE = 1000.0f / UPDATES_PER_SECOND;
    const float TICKS_PER_RENDER = 1000.0f / FRAMES_PER_SECOND;

    uint32_t lastUpdateTick = SDL_GetTicks();
    uint32_t lastRenderTick = SDL_GetTicks();
    uint32_t lastFPSCounterTick = lastUpdateTick;
    uint32_t FPS = 0;
    float ticksSinceUpdate = 0.0f;
    float ticksSinceRender = 0.0f;
    float timeScale = 1.0 / UPDATES_PER_SECOND;
    while(running) {

        // Determine how many ticks have passed since our last update then store the current tick
        // for next time
        uint32_t currentTicks = SDL_GetTicks();
        uint32_t ticksPassed = (currentTicks - lastUpdateTick);
        lastUpdateTick = currentTicks;

        ticksSinceUpdate += ticksPassed;

        // Process game logic N times, N being the amount of time (seconds) passed divided by 
        // how often we should process the logic every second
        while(ticksSinceUpdate >= TICKS_PER_UPDATE) {
            // Process events
            System::processEvents([&running](const SDL_Event& event) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                }
            });

            const float secondsPassed = TICKS_PER_UPDATE / 1000;

            // Process Input
            const Uint8 *kb = SDL_GetKeyboardState(NULL); 

            // Any logical game updates, position updates whatever go here
            running = running && game.run(kb, secondsPassed);

            checkSDLError();

            // Each update, reduce the amount of ticks since last update until we've updated
            // as many times as required based on TICKS_PER_UPDATE
            ticksSinceUpdate -= TICKS_PER_UPDATE;
        }
        
        currentTicks = SDL_GetTicks();
        ticksPassed = (currentTicks - lastRenderTick);
        lastRenderTick = currentTicks;

        ticksSinceRender += ticksPassed;

        if (ticksSinceRender >= TICKS_PER_RENDER) {

            // Render Scene.  
            //
            game.draw();
            FPS++;
            
            if ((currentTicks - lastFPSCounterTick) >= 1000) {
                w.setTitle(windowTitle + " [" + std::to_string(FPS) + "]");
                FPS = 0;
                lastFPSCounterTick += 1000;
            }

            float wholePart;
            float fractionalPart = std::modf(ticksSinceRender / TICKS_PER_RENDER, &wholePart);
            ticksSinceRender = ticksSinceRender - ((wholePart * TICKS_PER_RENDER) + (fractionalPart * TICKS_PER_RENDER));
        }
    }

    Logger::info("Window closed exiting application");

    return 0;
}

