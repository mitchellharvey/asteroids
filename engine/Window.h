#pragma once

#include "engine/Types.h"
#include "engine/Sprite.h"

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace thirstyfish {
class Window {
public:
    Window(const std::string& title = "Default Window",
           const glm::ivec2& size = {1024, 768},
           const glm::ivec2& pos = {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED}
    );

    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void show();
    void hide();
    void setTitle(const std::string& title);
    void setPosition(const glm::ivec2& position);
    void setSize(const glm::ivec2& size);

    std::string title() const;
    glm::ivec2 position() const;
    glm::ivec2 size() const;

    void render(std::vector<Sprite> sprites);

private:
    SDL_Window* _sdlWindow;
    SDL_Renderer* _sdlRenderer;

    SDL_Texture* textureFromSprite(const Sprite& sprite);

    std::unordered_map<AssetId, SDL_Texture*> _textureMap;
};
}
