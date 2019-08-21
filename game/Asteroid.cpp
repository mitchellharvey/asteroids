#include "Asteroid.h"

#include "engine/Logger.h"
#include "engine/String.h"
#include "engine/Utils.h"

#include <memory>
#include <cmath>
#include <SDL2/SDL.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

using thirstyfish::fmt;
using thirstyfish::Logger;
using thirstyfish::ANCHOR;
using thirstyfish::random;

Asteroid::Asteroid(AssetId imageId) :
_velocity(0.0f, -1.0f),
_maxSpeed(100.0f),
_minSpeed(10.0f),
_rotationSpeed(0.0f),
_maxRotationSpeed(180.0f),
_minRotationSpeed(0.1f)
{
    setImage(imageId);

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

void Asteroid::setImage(AssetId imageId) {
    const Image* image = Image::get(imageId);
    if (image) {
        _sprite.material = { imageId, SDL_Rect {0, 0, image->width(), image->height()}, ANCHOR::CENTER };

        float shrink = 0.2f;
        _sprite.size = { image->size().x * shrink, image->size().y * shrink };
    }
}

const Sprite& Asteroid::sprite() const {
    return _sprite;
}

void Asteroid::update(const Uint8* input, float elapsed) { 

    _sprite.rotation += (_rotationSpeed * elapsed);
    _sprite.position += (_velocity * elapsed);
}

void Asteroid::setPosition(glm::vec2 pos) {
    _sprite.position = pos;
}

glm::vec2 Asteroid::position() const {
    return _sprite.position;
}

