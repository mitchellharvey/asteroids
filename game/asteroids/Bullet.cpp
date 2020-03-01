#include "Bullet.h"

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

Bullet::Bullet(const glm::vec2& position, const glm::vec2& direction, AssetId imageId) :
_velocity(direction * 500.0f)
{
    setImage(imageId);
    _sprite.position = position;
}

Bullet::~Bullet() {
}

void Bullet::setImage(AssetId imageId) {
    const Image* image = Image::get(imageId);
    if (image) {
        _sprite.material = { imageId, SDL_Rect {0, 0, image->width(), image->height()}, ANCHOR::CENTER };

        float shrink = 0.10f;
        _sprite.size = { image->size().x * shrink, image->size().y * shrink };
    }
}

const Sprite& Bullet::sprite() const {
    return _sprite;
}

void Bullet::update(const Uint8* input, float elapsed) { 

    _sprite.position += (_velocity * elapsed);
}

void Bullet::setPosition(glm::vec2 pos) {
    _sprite.position = pos;
}

glm::vec2 Bullet::position() const {
    return _sprite.position;
}


