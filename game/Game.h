#pragma once

#include "engine/Window.h"
#include "engine/Sprite.h"
#include "engine/Image.h"

#include "Ship.h"

using thirstyfish::Window;
using thirstyfish::Image;
using thirstyfish::Sprite;

class Game {
public:
    Game(Window* window);
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    bool run(const Uint8* input, const float elapsed);
    void draw();

private:
    Window* _window;
    Ship _ship;
};

