#include "Game.h"
#include "engine/Logger.h"
#include "engine/String.h"

#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using thirstyfish::fmt;
using thirstyfish::Logger;
using thirstyfish::ANCHOR;

Game::Game() :
_shipImg("./assets/images/ship.png")
{
    _shipImg.load();

    _shipSprite.material = { _shipImg.id(), SDL_Rect {0, 0, _shipImg.width(), _shipImg.height()}, ANCHOR::CENTER };
    _shipSprite.position = {};

    float shrink = 0.2f;
    _shipSprite.size = { _shipImg.size().x * shrink, _shipImg.size().y * shrink };
}

Game::~Game() {
}

bool Game::run(const Uint8* input, float elapsed) {
    bool running = !input[SDL_SCANCODE_Q];

    _shipSprite.rotation += 100.0 * input[SDL_SCANCODE_D] * elapsed;
    _shipSprite.rotation -= 100.0 * input[SDL_SCANCODE_A] * elapsed;

    _shipSprite.position.y -= 100.0 * input[SDL_SCANCODE_W] * elapsed;
    _shipSprite.position.y += 100.0 * input[SDL_SCANCODE_S] * elapsed;

    glm::vec2 up(0.0f, 1.0f);
    glm::vec2 rotated = glm::rotate(up, 3.14f);

    Logger::info(fmt("Rotate {} by {} = {}", up, _shipSprite.rotation, rotated));

    return running;
}

void Game::draw(Window& window) {
    window.render({_shipSprite});
}
