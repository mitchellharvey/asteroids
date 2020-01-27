#pragma once

#include "asteroids/Ship.h"
#include "asteroids/Asteroid.h"

#include "Game.h"

#include "engine/Window.h"
#include "engine/Sprite.h"
#include "engine/Image.h"

#include <vector>

using thirstyfish::Window;
using thirstyfish::Image;
using thirstyfish::Sprite;

class Asteroids : public Game {
public:
    Asteroids(Window* window);
    ~Asteroids();

    Asteroids(const Asteroids&) = delete;
    Asteroids& operator=(const Asteroids&) = delete;

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


