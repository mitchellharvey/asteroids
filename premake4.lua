#!lua
solution "gl2d"
    configurations {"Debug" , "Release"}

    local common_flags = {
        "FatalWarnings",
        "StaticRuntime",
    }


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
            defines { "DEBUG" }
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
        includedirs { "./engine" }
        links { "engine" }
        flags(common_flags)

        files {
            "./game/*.cpp",
            "./game/*.h",
        }

        configuration "Debug"
            defines { "DEBUG" }
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


