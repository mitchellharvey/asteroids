#!lua
solution "Asteroids"
    configurations {"Debug" , "Release"}

    local common_flags = {
        "FatalWarnings",
        "StaticRuntime",
    }

    links { "pthread", "SDL2", "SDL2_image" }
    includedirs { "./" }

    configuration { "gmake" }
        buildoptions {"-std=c++14"}

    project "Engine"
        kind "StaticLib"
        language "C++"
        targetname "engine"
        flags(common_flags)

        files {
            "./engine/*.cpp",
            "./engine/*.h"
        }

        configuration "Debug"
            defines { "_DEBUG" }
            targetdir "./build/engine/Debug"
            objdir "./build/engine/Debug/obj"
            flags {"Symbols"}

        configuration "Release"
            defines { "NDEBUG" }
            targetdir "./build/engine/Release"
            objdir "./build/engine/Release/obj"
            flags {"Optimize"}

    project "Game"
        kind "WindowedApp"
        language "C++"
        targetname "game"
        links { "engine" }
        flags(common_flags)

        files {
            "./game/*.cpp",
            "./game/*.h",
        }

        configuration "Debug"
            defines { "_DEBUG" }
            targetdir "./build/game/Debug"
            objdir "./build/game/Debug/obj"
            libdirs {"./build/engine/Debug"}
            flags {"Symbols"}

        configuration "Release"
            defines { "NDEBUG" }
            targetdir "./build/game/Release"
            objdir "./build/game/Release/obj"
            libdirs {"./build/engine/Release"}
            flags {"Optimize"}


