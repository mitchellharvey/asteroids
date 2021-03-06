#pragma once

#include "GameObject.h"

#include "engine/Image.h"

using thirstyfish::Sprite;
using thirstyfish::Image;
using thirstyfish::AssetId;
using thirstyfish::ASSET_ID_CONSTANTS::NONE;

class Ship : public GameObject {
public:
    Ship(AssetId imageId = NONE);
    ~Ship();

    void update(const Uint8* input, float elapsed);

    void setImage(AssetId imageId);
    void setPosition(glm::vec2 pos);

    glm::vec2 position() const;
    const Sprite& sprite() const;

private:
    Sprite _sprite;
    glm::vec2 _velocity;

    float _maxSpeed;
    float _rotationSpeed;

    float _accelerationRate;

    float _dragRate;
    float _dragSpeedKickin;
};

