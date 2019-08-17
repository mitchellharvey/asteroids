#pragma once

#include "engine/Sprite.h"
#include "engine/Image.h"

using thirstyfish::Sprite;
using thirstyfish::Image;

class Ship {
public:
    Ship();
    ~Ship();

    void update(const Uint8* input, float elapsed);
    const Sprite& sprite() const;

private:
    Image _img;
    Sprite _sprite;
    glm::vec2 _velocity;

    float _maxSpeed;
    float _rotationSpeed;

    float _accelerationRate;

    float _dragRate;
    float _dragSpeedKickin;
};



