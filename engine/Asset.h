#pragma once

#include "engine/Types.h"

namespace thirstyfish {
class Asset {
public:
    Asset();
    virtual ~Asset() = 0;

    AssetId id() const;

    Asset(const Asset&) = delete;
    Asset& operator=(const Asset&) = delete;

protected:
    void newAssetId();

    AssetId _id;
};
}


