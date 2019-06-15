#pragma once

#include "engine/Window.h"
#include "engine/Sprite.h"
#include "engine/Image.h"

using thirstyfish::Window;
using thirstyfish::Image;
using thirstyfish::Sprite;

class Game {
public:
    Game();
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    bool run(const Uint8* input, const float elapsed);
    void draw(Window& window);

private:
    Image _shipImg;
    Sprite _shipSprite;
};

