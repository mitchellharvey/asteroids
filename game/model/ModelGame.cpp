#include "model/ModelGame.h"

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

ModelGame::ModelGame(Window* window) :
_window(window)
{
    if (_window) {
        glm::vec2 windowSize = _window->size();
    }
}

ModelGame::~ModelGame() {
}

bool ModelGame::run(const Uint8* input, float elapsed) {
    bool running = !input[SDL_SCANCODE_Q];
    return running;
}

void ModelGame::draw() {
    if (_window) {
        _window->render({});
    }

}

