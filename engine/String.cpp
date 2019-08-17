#include "engine/String.h"

namespace thirstyfish {
    std::string str(int v) {
        return std::to_string(v);
    }

    std::string str(unsigned int v) {
        return std::to_string(v);
    }

    std::string str(float v) {
        return std::to_string(v);
    }

    std::string str(AssetId id) {
        return std::to_string(id);
    }

    const std::string& str(const std::string& string) {
        return string;
    }

    std::string str(const char* cstr) {
        return std::string(cstr);
    }

    std::string str(void* v) {
        char buff[32] = {0};
        snprintf(buff, sizeof(buff), "%p", v);
        return std::string(buff);
    }

    std::string str(const glm::vec2& v) {
        char buff[32] = {0};
        snprintf(buff, sizeof(buff), "(%f, %f)", v.x, v.y);
        return std::string(buff);
    }

    std::string fmt(const std::string& format) {
        return format;
    }
}
