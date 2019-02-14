#include "engine/Asset.h"

#include <atomic>

namespace {
    using namespace thirstyfish;
    std::atomic<AssetId> _nextAssetId(__AID_INTERNAL_ASSET_ID_START);
}

namespace thirstyfish {
Asset::Asset() : 
_id(0) {
    newAssetId();
}

Asset::~Asset() {
}

void Asset::newAssetId() {
    _id = std::atomic_fetch_add(&_nextAssetId, 1ul);
}

AssetId Asset::id() const {
    return _id;
}
}

