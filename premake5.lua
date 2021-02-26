workspace "onyx"
    configurations { "debug", "release" }

project "onyx"
    kind "StaticLib"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}/onyx"
    objdir "bin/%{cfg.buildcfg}/onyx"

    includedirs {
        "include",
        "include/vendor",
        "/usr/local/include/freetype2"
    }

    files {
        "include/**.h", "src/**.cpp"
    }

    filter "configurations:debug"
        symbols "On"

    filter "configurations:release"
        optimize "On"
        runtime "Release"

project "test"
    kind "ConsoleApp"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}/test"
    objdir "obj/%{cfg.buildcfg}/test"

    includedirs {
        "include",
        "include/vendor",
        "/usr/local/include/freetype2"
    }

    libdirs {
        "bin/%{cfg.buildcfg}/onyx"
    }

    files {
        "test/**.h", "test/**.cpp"
    }

    links {
        "onyx",
        "dl",
        "GL",
        "glfw",
        "GLEW",
        "openal",
        "freetype"
    }

    filter "configurations:debug"
        symbols "On"

    filter "configurations:release"
        optimize "On"
        runtime "Release"