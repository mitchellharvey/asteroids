#include "Asteroid.h"

#include "engine/Logger.h"
#include "engine/String.h"
#include "engine/Utils.h"

#include <cmath>
#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using thirstyfish::fmt;
using thirstyfish::Logger;
using thirstyfish::ANCHOR;
using thirstyfish::random;

Asteroid::Asteroid() :
_img("./assets/images/asteroid.png"),
_velocity(0.0f, -1.0f),
_maxSpeed(500.0f),
_minSpeed(10.0f),
_rotationSpeed(0.0f),
_maxRotationSpeed(360.0f),
_minRotationSpeed(0.1f)
{
    _img.load();

    _sprite.material = { _img.id(), SDL_Rect {0, 0, _img.width(), _img.height()}, ANCHOR::CENTER };
    _sprite.position = {};

    float shrink = 0.2f;
    _sprite.size = { _img.size().x * shrink, _img.size().y * shrink };

    // Generate a random movement direction
    float randomAngle = random(0.0f, 359.99f);
    _velocity = glm::normalize(glm::rotate(_velocity, glm::radians(randomAngle)));

    float randomSpeed = random(_minSpeed, _maxSpeed);
    _velocity = _velocity * randomSpeed;

    // Random rotation speed
    _rotationSpeed = random(_minRotationSpeed, _maxRotationSpeed);
}

Asteroid::~Asteroid() {
}

const Sprite& Asteroid::sprite() const {
    return _sprite;
}

void Asteroid::update(const Uint8* input, float elapsed) { 

    _sprite.rotation += (_rotationSpeed * elapsed);
    _sprite.position += (_velocity * elapsed);
}

void Asteroid::position(glm::vec2 pos) {
    _sprite.position = pos;
}

glm::vec2 Asteroid::position() const {
    return _sprite.position;
}

