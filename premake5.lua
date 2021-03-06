workspace "onyx"
    configurations { "debug", "release" }

project "onyx"
    kind "StaticLib"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}/onyx"
    objdir "obj/%{cfg.buildcfg}/onyx"

    includedirs {
        "include/",
        "include/onyx/vendor",
        "/usr/local/include/freetype2"
    }

    files {
        "include/onyx/**.h", "src/onyx/**.cpp"
    }

    filter "configurations:debug"
        symbols "On"

    filter "configurations:release"
        optimize "On"
        runtime "Release"

project "editor"
    kind "ConsoleApp"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}/editor"
    objdir "obj/%{cfg.buildcfg}/editor"

    includedirs {
        "include",
        "include/editor/vendor",
        "include/editor/vendor/imgui",
        "/usr/local/include/freetype2"
    }

    libdirs {
        "bin/%{cfg.buildcfg}/onyx"
    }

    files {
        "include/editor/**.h", "src/editor/**.cpp"
    }

    links {
        "onyx",
        "dl",
        "GL",
        "glfw",
        "GLEW",
        "openal",
        "freetype",
        "box2d"
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
        "freetype",
        "box2d"
    }

    filter "configurations:debug"
        symbols "On"

    filter "configurations:release"
        optimize "On"
        runtime "Release"