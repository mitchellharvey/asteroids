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
_window(window) 
{
    if (_window) {
        glm::vec2 center = _window->size() / 2;
        _ship.position(center);
        Logger::debug(fmt("Window size {}, center {}", _window->size(), center));
    }
}

Game::~Game() {
}

bool Game::run(const Uint8* input, float elapsed) {
    bool running = !input[SDL_SCANCODE_Q];

    _ship.update(input, elapsed);

    return running;
}

void Game::draw() {
    if (_window) {
        _window->render({_ship.sprite()});
    }
}
