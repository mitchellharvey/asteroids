#pragma once

#include "asteroids/Ship.h"
#include "asteroids/Asteroid.h"
#include "asteroids/Bullet.h"

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
    Image _bulletImage;

    void boundsCheckObject(GameObject& obj);
    void fireBullet();
    bool outOfBounds(const GameObject& obj);

    Window* _window;
    Ship _ship;
    std::vector<Asteroid> _asteroids;

    std::vector<Bullet> _bullets;

    int _minAsteroids;
    int _maxAsteroids;
    float _bulletsPerSecond;
    float _elapsedSinceLastBullet;
    SDL_Rect _gameBounds;
    SDL_Rect _visibleBounds;;
};


