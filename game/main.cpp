

#include "engine/System.h"
#include "engine/Window.h"
#include "engine/Logger.h"
#include "engine/Image.h"
#include "engine/Sprite.h"

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <cmath>

using namespace thirstyfish;

int main(int argc, char** argv) {

    Logger::logLevel(Logger::Level::DEBUG);

    if (!System::init()) {
        Logger::error("Failure during system initialization.  Exiting");
        return 1;
    }

    std::string windowTitle = "Asteroids!";
    Window w(windowTitle, glm::vec2(1920, 1080));

    Image shipImg("./assets/images/ship.png");
    shipImg.load();

    Sprite ship; 
    ship.material = { shipImg.id(), SDL_Rect {0, 0, shipImg.width(), shipImg.height()} };
    ship.position = {};
    ship.size = shipImg.size();

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
            System::processEvents([&running, &ship](const SDL_Event& event) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                }
            });

            // Process Input
            const Uint8 *kb = SDL_GetKeyboardState(NULL); 
            ship.position.x += 1.0 * kb[SDL_SCANCODE_D];
            ship.position.x -= 1.0 * kb[SDL_SCANCODE_A];
            ship.position.y -= 1.0 * kb[SDL_SCANCODE_W];
            ship.position.y += 1.0 * kb[SDL_SCANCODE_S];

            // Any logical game updates, position updates whatever go here

            // Each update, reduce the amount of ticks since last update until we've updated
            // as many times as required based on TICKS_PER_UPDATE
            ticksSinceUpdate -= TICKS_PER_UPDATE;
        }
        
        currentTicks = SDL_GetTicks();
        ticksPassed = (currentTicks - lastRenderTick);
        lastRenderTick = currentTicks;

        ticksSinceRender += ticksPassed;

        if (ticksSinceRender >= TICKS_PER_RENDER) {

            // Render Scene.  The Frame Rate is inherinetly clamped to the update rate.  If we didn't do this
            // and put render outside of the tick loop, we get the diablo effect during lag, where the game speeds
            // up to catch up.
            //
            w.render( {ship} );
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

