#pragma once

#include "Game.h"

#include "engine/Window.h"
#include "engine/Sprite.h"
#include "engine/Image.h"

using thirstyfish::Window;

class ModelGame : public Game {
public:
    ModelGame(Window* window);
    ~ModelGame();

    ModelGame(const ModelGame&) = delete;
    ModelGame& operator=(const ModelGame&) = delete;

    bool run(const Uint8* input, const float elapsed);
    void draw();

private:
    Window* _window;
};


