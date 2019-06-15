#pragma once

#include <glm/vec2.hpp>
#include <string>

namespace thirstyfish {
    std::string str(int v);
    std::string str(float v);
    std::string str(unsigned int v);
    std::string str(void* v);
    std::string str(const glm::vec2& v);

    template<typename T>
    std::string str(T* v) {
        return str(static_cast<void *>(v));
    }

    std::string fmt(const std::string& format);

    template<typename T, typename... Targs>
    std::string fmt(const std::string& format, T arg, Targs... args) {
        std::string result;
        size_t size = format.size();
        bool escape = false;
        bool options = false;
        for(size_t i = 0; i < size; ++i) {
            if (escape) {
                result += format[i];
                escape = false;
            } else {
                switch (format[i]) 
                {
                    case '\\':
                    {
                        escape = true;
                    } break;
                    case '{': 
                    {
                        options = true;
                    } break;
                    case '}': 
                    {
                        options = false;
                        result += str(arg);
                        return result + fmt(&format[i] + 1, args...);
                    } break;
                    default: 
                    {
                        if (options) {
                        } else {
                            result += format[i];
                        }
                    }
                };
            }
        }

        return result;
    }
}

