#include "Game.h"
#include "engine/Logger.h"
#include "engine/String.h"

#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/trigonometric.hpp>
#include <algorithm>

using thirstyfish::fmt;
using thirstyfish::Logger;
using thirstyfish::ANCHOR;

Game::Game(Window* window) :
_window(window),
_ship(Ship()),
_asteroids(1)
{
    if (_window) {
        glm::vec2 center = _window->size() / 2;
        _ship.position(center);
        glm::vec2 windowSize = _window->size();
        Logger::debug(fmt("Window size {}, center {}", windowSize, center));

        Asteroid& a = _asteroids[0];
        a.position({center.x, 0.0f});

        _visibleBounds = {0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)};

        int margin = _ship.sprite().size.x;
        _gameBounds = {-margin, -margin, _visibleBounds.w + margin, _visibleBounds.h + margin};
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
