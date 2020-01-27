#pragma once

#include "engine/Window.h"
#include "engine/Sprite.h"
#include "engine/Image.h"

#include <vector>

using thirstyfish::Window;
using thirstyfish::Image;
using thirstyfish::Sprite;

class Game {
public:
    virtual ~Game() {};

    virtual bool run(const Uint8* input, const float elapsed) = 0;
    virtual void draw() = 0;
};

