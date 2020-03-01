#include "asteroids/Asteroids.h"

#include "engine/Logger.h"
#include "engine/String.h"
#include "engine/Utils.h"

#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/trigonometric.hpp>
#include <algorithm>

using thirstyfish::fmt;
using thirstyfish::Logger;
using thirstyfish::ANCHOR;
using thirstyfish::random;

Asteroids::Asteroids(Window* window) :
_window(window),
_ship(Ship()),
_minAsteroids(2),
_maxAsteroids(4), 
_bulletsPerSecond(3), 
_elapsedSinceLastBullet(0.0)
{
    if (_window) {
        glm::vec2 windowSize = _window->size();

        // Setup game boundaries
        _visibleBounds = {0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)};

        // Load Images 
        _asteroidImage = Image("./assets/images/asteroid.png"); 
        _asteroidImage.load();

        _shipImage = Image("./assets/images/ship.png");
        _shipImage.load();

        _bulletImage = Image("./assets/images/bullet.png");
        _bulletImage.load();

        // Initialize Ship
        glm::vec2 center = _window->size() / 2;
        _ship.setPosition(center);
        _ship.setImage(_shipImage.id());

        int margin = _ship.sprite().size.x * 2.0f;
        _gameBounds = {-margin, -margin, _visibleBounds.w + margin, _visibleBounds.h + margin};

        // Initialize asteroids
        int totalAsteroids = random(_minAsteroids, _maxAsteroids);
        Logger::debug(fmt("Total asteroids: {}", totalAsteroids));

        _asteroids.resize(totalAsteroids);

        glm::vec2 randomStart;
        for (Asteroid& a : _asteroids) {
            int quad = random(0, 3);
            switch(quad) {
                case 0:
                    randomStart = {random(_gameBounds.x, _gameBounds.w), _visibleBounds.y};
                    break;
                case 1:
                    randomStart = {random(_gameBounds.x, _gameBounds.w), _visibleBounds.h};
                    break;
                case 2:
                    randomStart = {_visibleBounds.x, random(_gameBounds.y, _gameBounds.h)};
                    break;
                default:
                    randomStart = {_visibleBounds.w, random(_gameBounds.y, _gameBounds.h)};
                    break;
            }

            a.setImage(_asteroidImage.id());
            a.setPosition(randomStart);
        }
    }
}

Asteroids::~Asteroids() {
}

void Asteroids::boundsCheckObject(GameObject& obj) {

    // Check for collisions
    // Rename, this is general for asteroids and ships and maybe other shitj
    SDL_Rect shipBounds = obj.sprite().bounds();
    glm::vec2 new_pos(obj.position());
    if (shipBounds.x >= _gameBounds.w) {
        new_pos.x = _visibleBounds.x - shipBounds.w * 0.5f;
    } else if (shipBounds.x < _gameBounds.x) {
        new_pos.x = _visibleBounds.w + shipBounds.w * 0.5f;
    }

    if (shipBounds.y >= _gameBounds.h) {
        new_pos.y = _visibleBounds.y - shipBounds.h * 0.5f;
    } else if (shipBounds.y < _gameBounds.y) {
        new_pos.y = _visibleBounds.h + shipBounds.h * 0.5f;
    }

    obj.setPosition(new_pos);
}

bool Asteroids::outOfBounds(const GameObject& obj) {
    SDL_Rect objBounds = obj.sprite().bounds();

    return  objBounds.x >= _gameBounds.w ||
            objBounds.x <= _gameBounds.x ||
            objBounds.y <= _gameBounds.y ||
            objBounds.y >= _gameBounds.h;
}

bool Asteroids::run(const Uint8* input, float elapsed) {
    bool running = !input[SDL_SCANCODE_Q];


    bool spaceDown = input[SDL_SCANCODE_SPACE];

    _elapsedSinceLastBullet += elapsed;

    float timePerBullet = 1.0f / _bulletsPerSecond;
    bool shootBullet = _elapsedSinceLastBullet >= timePerBullet;
    if (spaceDown && shootBullet) {
        fireBullet();
        _elapsedSinceLastBullet = 0;
    }

    // Update our game objects
    _ship.update(input, elapsed);
    boundsCheckObject(_ship);

    for (Asteroid& a : _asteroids) {
        a.update(input, elapsed);
        boundsCheckObject(a);
    }

    for(auto it = _bullets.begin(); it != _bullets.end();) {
        Bullet& b = *it;
        b.update(input, elapsed);

        if (outOfBounds(b)) {
            it = _bullets.erase(it);
        } else {
            it++;
        }
    }

    return running;
}

void Asteroids::draw() {

    if (_window) {
        std::vector<Sprite> renderables;
        renderables.push_back(_ship.sprite());
        for(Asteroid& a : _asteroids) {
            renderables.push_back(a.sprite());
        }

        for(Bullet& b : _bullets) {
            renderables.push_back(b.sprite());
        }

        _window->render(renderables);
    }
}

void Asteroids::fireBullet() { 

    Bullet b(
        _ship.position(),
        _ship.sprite().localYAxis(),
        _bulletImage.id()
    );

    _bullets.push_back(b);
}
