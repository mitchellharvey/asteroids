#include "engine/Window.h"
#include "engine/Logger.h"

namespace thirstyfish {
Window::Window() :
    Window("Default Title",
            glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
            glm::ivec2(1024, 768))
{
}

Window::~Window() {
    if (_sdlRenderer) {
        Logger::info("Destroying SDL Window Renderer");
        SDL_DestroyRenderer(_sdlRenderer);
        _sdlRenderer = nullptr;
    }

    if (_sdlWindow) {
        Logger::info("Destroying SDL Window");
        SDL_DestroyWindow(_sdlWindow);
        _sdlWindow = nullptr;
    }
}

Window::Window(const std::string& title, const glm::ivec2& pos, const glm::ivec2& size) :
_sdlWindow(nullptr),
_sdlRenderer(nullptr) {

    Logger::info("Creating SDL Window");
    _sdlWindow = SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, SDL_WINDOW_SHOWN);
    if (!_sdlWindow) {
        Logger::error("Failed to create SDL Window");
        Logger::error(SDL_GetError());
    } else {
        Logger::info("Creating SDL Window Renderer");
        _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    }
}

void Window::show() {
    SDL_ShowWindow(_sdlWindow);
}

void Window::hide() {
    SDL_HideWindow(_sdlWindow);
}

void Window::setTitle(const std::string& title) {
    SDL_SetWindowTitle(_sdlWindow, title.c_str());
}

void Window::setPosition(const glm::ivec2& position) {
    SDL_SetWindowPosition(_sdlWindow, position.x, position.y);
}

void Window::setSize(const glm::ivec2& size) {
    SDL_SetWindowSize(_sdlWindow, size.x, size.y);
}

std::string Window::title() const {
    return std::string(SDL_GetWindowTitle(_sdlWindow));
}

glm::ivec2 Window::position() const {
    glm::ivec2 pos;
    SDL_GetWindowPosition(_sdlWindow, &pos.x, &pos.y);
    return pos;
}

glm::ivec2 Window::size() const {
    glm::ivec2 size;
    SDL_GetWindowPosition(_sdlWindow, &size.x, &size.y);
    return size;
}
}

