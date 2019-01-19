#include <iostream>
using namespace std;

#include <SDL2/SDL.h>

int main(int argc, char** argv) {

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface =nullptr;

    /*
    int viddrivers = SDL_GetNumVideoDrivers();
    cout << "Total Video Drivers: " << viddrivers << endl;
    for (int i = 0; i < viddrivers; ++i) {
        const char* drivername = SDL_GetVideoDriver(i);

        if (SDL_VideoInit(drivername) == 0) {
            SDL_VideoQuit();
            cout << "Driver " << drivername << " works." << endl;
        } else {
            cout << "Driver " << drivername << " doesn't work." << endl;
        }
    }
    */

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        cout << "Failed to initialize SDL [" << SDL_GetError() << "]" << endl;
    } else {
        window = SDL_CreateWindow("Asteroids" , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
        if (!window) {
            cout << "Failed to create SDL Window" << endl;
        } else {
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }

    return 0;
}

