#include "Game.h"
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

Game::Game(Window* window) :
_window(window),
_ship(Ship()),
_minAsteroids(2),
_maxAsteroids(4)
{
    if (_window) {
        glm::vec2 center = _window->size() / 2;
        _ship.position(center);
        glm::vec2 windowSize = _window->size();
        Logger::debug(fmt("Window size {}, center {}", windowSize, center));

        // Setup game boundaries
        _visibleBounds = {0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)};

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
            a.position(randomStart);
        }
    }
}

Game::~Game() {
}

void Game::boundsCheckObject(GameObject& obj) {
    
    // Check for collisions
    SDL_Rect shipBounds = obj.sprite().bounds();
    glm::vec2 shipPos = obj.position();
    if (shipBounds.x >= _gameBounds.w) {
        glm::vec2 new_pos(shipPos);
        new_pos.x = _visibleBounds.x - shipBounds.w * 0.5f;
        obj.position(new_pos);
    } else if (shipBounds.x < _gameBounds.x) {
        glm::vec2 new_pos(shipPos);
        new_pos.x = _visibleBounds.w + shipBounds.w * 0.5f;
        obj.position(new_pos);
    }

    if (shipBounds.y >= _gameBounds.h) {
        glm::vec2 new_pos(shipPos);
        new_pos.y = _visibleBounds.y - shipBounds.h * 0.5f;
        obj.position(new_pos);
    } else if (shipBounds.y < _gameBounds.y) {
        glm::vec2 new_pos(shipPos);
        new_pos.y = _visibleBounds.h + shipBounds.h * 0.5f;
        obj.position(new_pos);
    }
}

bool Game::run(const Uint8* input, float elapsed) {
    bool running = !input[SDL_SCANCODE_Q];

    // Update our game objects
    _ship.update(input, elapsed);
    boundsCheckObject(_ship);

    for (Asteroid& a : _asteroids) {
        a.update(input, elapsed);
        boundsCheckObject(a);
    }

    return running;
}

void Game::draw() {

    if (_window) {
        std::vector<Sprite> renderables;
        renderables.push_back(_ship.sprite());
        for(Asteroid& a : _asteroids) {
            renderables.push_back(a.sprite());
        }

        _window->render(renderables);
    }
}
