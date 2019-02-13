#pragma once

#include <string>

namespace thirstyfish {

class AssetManager {
public:
    static void setAssetRootPath(const std::string& rootDir);

    /*
    static AssetId createTexture(const std::string& filePath);
    static void destroyTexture(const AssetId textureId);
    static void destroyAllTextures();
    */

    AssetManager() = delete;
    ~AssetManager() = delete;
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
};
}

