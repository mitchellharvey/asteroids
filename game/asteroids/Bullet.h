#pragma once

#include "GameObject.h"
#include "engine/Image.h"

using thirstyfish::Sprite;
using thirstyfish::Image;
using thirstyfish::AssetId;
using thirstyfish::ASSET_ID_CONSTANTS::NONE;

class Bullet : public GameObject {
public:
    Bullet(const glm::vec2& position, const glm::vec2& direction, AssetId imageId = NONE);
    ~Bullet();

    void update(const Uint8* input, float elapsed);

    void setImage(AssetId imageId);
    void setPosition(glm::vec2 pos);

    glm::vec2 position() const;
    const Sprite& sprite() const;

private:

    Sprite _sprite;
    glm::vec2 _velocity;
};



