#include "engine/Window.h"
#include "engine/Image.h"
#include "engine/Logger.h"
#include "engine/String.h"

namespace thirstyfish {
Window::Window(const std::string& title, const glm::ivec2& size,  const glm::ivec2& pos) :
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
        //SDL_GL_SetSwapInterval(0);
    }
}

Window::~Window() {

    // Unload any hardware textures
    for (const auto &kv : _textureMap) {
        SDL_DestroyTexture(kv.second);
    }
    _textureMap.clear();

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
    SDL_GetWindowSize(_sdlWindow, &size.x, &size.y);
    return size;
}

void Window::render(const std::vector<Sprite>& sprites) {

    if (_sdlRenderer) {
        SDL_SetRenderDrawColor(_sdlRenderer, 0,0,0,255);
        SDL_RenderClear(_sdlRenderer);
        for(const Sprite &s : sprites) {
            SDL_Texture* texture = textureFromSprite(s);
            SDL_Rect dest = s.bounds();
            SDL_RenderCopyEx(_sdlRenderer, texture, &s.material.imageRect, &dest, s.rotation, nullptr, SDL_FLIP_NONE);
        }
        SDL_RenderPresent(_sdlRenderer);
    }
}

SDL_Texture* Window::textureFromSprite(const Sprite& sprite) {

    AssetId imageId = sprite.material.image;
    
    // Try to find already loaded hardware texture 
    auto f = _textureMap.find(imageId);
    if (f != _textureMap.end()) {
        return f->second;
    }

    // Load hardware texture from sprite image
    SDL_Texture* texture = nullptr;
    const Image* img = Image::get(imageId);
    if (img) {
        texture = img->createTexture(_sdlRenderer);
        if (texture) {
            _textureMap.emplace(imageId, texture);
        } else {
            Logger::error(fmt("Failed to create hardware texture from image [id: {}] {}", imageId, img->filePath()));
        }
    } else {
        Logger::error(fmt("Failed to get Image from image id {}", imageId));
    }

    return texture;
}

}

