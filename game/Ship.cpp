#include "Ship.h"

#include "engine/Logger.h"
#include "engine/String.h"

#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using thirstyfish::fmt;
using thirstyfish::Logger;
using thirstyfish::ANCHOR;

Ship::Ship() :
_img("./assets/images/ship.png"),
_velocity(0.0f, 0.0f),
_maxSpeed(500.0f),
_rotationSpeed(100.0f),
_accelerationRate(200.0f),
_dragRate(50.0f),
_dragSpeedKickin(10.0f)
{
    _img.load();

    _sprite.material = { _img.id(), SDL_Rect {0, 0, _img.width(), _img.height()}, ANCHOR::CENTER };
    _sprite.position = {};

    float shrink = 0.2f;
    _sprite.size = { _img.size().x * shrink, _img.size().y * shrink };
}

Ship::~Ship() {
}
const Sprite& Ship::sprite() const {
    return _sprite;
}

void Ship::update(const Uint8* input, float elapsed) { 

    bool accelerate = input[SDL_SCANCODE_W] == 1;
    bool deccelerate = input[SDL_SCANCODE_S] == 1;
    bool rotateRight = input[SDL_SCANCODE_D] == 1;
    bool rotateLeft = input[SDL_SCANCODE_A] == 1;

    // Apply rotation to the ship
    float rotate = 0.0f;
    if (rotateRight) {
        rotate += _rotationSpeed * elapsed;
    }

    if (rotateLeft) {
        rotate -= _rotationSpeed * elapsed;
    }
    _sprite.rotation += rotate;

    // Apply acceleration/decceleration to the velocity
    float accel = 0.0f;
    if (accelerate) {
        accel += _accelerationRate * elapsed;
    }

    if (deccelerate) {
        accel -= _accelerationRate * elapsed;
    }

    float speed = glm::length(_velocity) + accel;
    glm::vec2 acceleration = _sprite.localYAxis() * accel;
    if (speed < _maxSpeed && speed > -_maxSpeed) {
        _velocity += acceleration;
    }

    // Apply Drag to the velocity
    if (!accelerate && !deccelerate) {
        if (speed > _dragSpeedKickin) {
            _velocity -= glm::normalize(_velocity) * _dragRate * elapsed;
        } else if (speed < -_dragSpeedKickin) {
            _velocity += glm::normalize(_velocity) * _dragRate * elapsed;
        }
    }


    // Apply velocity to sprite position
    _sprite.position += (_velocity * elapsed);

    //Logger::debug(fmt("Ship Position: {}", _sprite.position));
}


void Ship::position(glm::vec2 pos) {
    _sprite.position = pos;
    //Logger::debug(fmt("Set Ship Position: {}", _sprite.position));
}

glm::vec2 Ship::position() const {
    return _sprite.position;
}
