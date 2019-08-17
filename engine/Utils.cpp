#include "engine/Utils.h"

#include <random>

namespace {
    unsigned int SEED = 0;
    std::random_device RANDOM_DEVICE;
    std::mt19937 RANDOM_ENGINE(RANDOM_DEVICE());
}

namespace thirstyfish {

void seed(unsigned int s) {
    SEED = s;
}

unsigned int seed() {
    return SEED;
}

float random(float min, float max) {
    std::uniform_real_distribution<float> d(min, max);
    return d(RANDOM_ENGINE);
}

}

