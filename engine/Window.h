#pragma once

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>
#include <string>

namespace thirstyfish {
class Window {
public:
    Window();
    Window(const std::string& title, const glm::ivec2& pos, const glm::ivec2& size);
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

private:
    SDL_Window* _sdlWindow;
    SDL_Renderer* _sdlRenderer;
};
}
