#pragma once

#include "engine/Sprite.h"

using thirstyfish::Sprite;

class GameObject {
public:
    virtual void update(const Uint8* input, float elapsed) = 0;
    virtual const Sprite& sprite() const = 0;

    virtual void setPosition(glm::vec2 pos) = 0;
    virtual glm::vec2 position() const = 0;
};


