#include "engine/Sprite.h"
#include "engine/Logger.h"
#include "engine/Image.h"

namespace thirstyfish {
void Sprite::render(SDL_Renderer* renderer) {
    if (renderer) {
        const Image* img = Image::get(material.image);
        if (img) {
            // TODO: FIX THIS ASPA, just leaking textures atm
            SDL_Texture* t = img->createTexture(renderer);
            if (!t) {
                Logger::error("Failed to create texture!");
            }
            SDL_Rect dest {position.x, position.y, size.x, size.y};
            SDL_RenderCopyEx(renderer, t, &material.imageRect, &dest, 0.0, nullptr, SDL_FLIP_NONE);
        } else {
            Logger::error("NO IMAGE");
        }
    }
}
}

