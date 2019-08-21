#pragma once

#include "engine/Window.h"
#include "engine/Sprite.h"
#include "engine/Image.h"

#include <vector>

#include "Ship.h"
#include "Asteroid.h"

using thirstyfish::Window;
using thirstyfish::Image;
using thirstyfish::Sprite;

class Game {
public:
    Game(Window* window);
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    bool run(const Uint8* input, const float elapsed);
    void draw();

private:
    Image _asteroidImage;
    Image _shipImage;

    void boundsCheckObject(GameObject& obj);

    Window* _window;
    Ship _ship;
    std::vector<Asteroid> _asteroids;
    int _minAsteroids;
    int _maxAsteroids;
    SDL_Rect _gameBounds;
    SDL_Rect _visibleBounds;;
};

