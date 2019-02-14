#pragma once

#include <cstdint>

namespace thirstyfish {
    using AssetId = uint64_t;

    enum ASSET_ID_CONSTANTS : AssetId {
        NONE,
        __AID_INTERNAL_ASSET_ID_START
    };
}
