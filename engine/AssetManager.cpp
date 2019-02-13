#include "engine/AssetManager.h"
#include "engine/Logger.h"

#include <mutex>
#include <unordered_map>

namespace {
    using namespace thirstyfish;
    std::string _assetRootPath;
    std::mutex _mutex;
    //std::unordered_map<AssetId, Texture*> _textures;

    std::string normalizePath(const std::string& base, const std::string& path) {
        // TODO: Make this robust
        return base + path;
    }
}

namespace thirstyfish {
void AssetManager::setAssetRootPath(const std::string& rootDir) {
    Logger::info("Set Asset Root Path: " + rootDir);

    std::lock_guard<std::mutex> guard(_mutex);

    _assetRootPath = rootDir;
}

/*
AssetId AssetManager::createTexture(const std::string& filePath) {
    Logger::info("Load Texture: " + filePath);

    std::lock_guard<std::mutex> guard(_mutex);

    const std::string fullPath(normalizePath(_assetRootPath, filePath));

    Texture *texture = new Texture(fullPath);

    AssetId id = texture->id();
    _textures[id] = texture;

    Logger::info("Loaded Texture id: " + std::to_string(id));
    return id;
}

void AssetManager::destroyTexture(const AssetId textureId) {
    Logger::info("Destroy Texture: " + std::to_string(textureId));

    std::lock_guard<std::mutex> guard(_mutex);

    auto found = _textures.find(textureId);
    if (found != _textures.end()) {
        delete found->second;
        _textures.erase(found);
        Logger::info("Destroyed Texture: " + std::to_string(textureId));
    }
}

void AssetManager::destroyAllTextures() {
    Logger::info("Destroy all textures");

    std::lock_guard<std::mutex> guard(_mutex);

    for ( auto i = _textures.begin(); i != _textures.end(); ++i) {
        delete i->second;
    }
    _textures.clear();
}
*/

}
