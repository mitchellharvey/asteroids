#pragma once

#include "GameObject.h"

#include "engine/Image.h"

using thirstyfish::Sprite;
using thirstyfish::Image;

class Asteroid : public GameObject {
public:
    Asteroid();
    ~Asteroid();

    void update(const Uint8* input, float elapsed);
    const Sprite& sprite() const;

    void position(glm::vec2 pos);
    glm::vec2 position() const;

private:
    Image _img;
    Sprite _sprite;
    glm::vec2 _velocity;

    float _maxSpeed;
    float _minSpeed;

    float _rotationSpeed;
    float _maxRotationSpeed;
    float _minRotationSpeed;
};


