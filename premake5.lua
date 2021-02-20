workspace "onyx"
    configurations { "debug", "release" }

project "onyx"
    kind "StaticLib"

    targetdir "bin/%{cfg.buildcfg}/onyx"
    objdir "bin/%{cfg.buildcfg}/onyx"

    includedirs {
        "include"
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

    targetdir "bin/%{cfg.buildcfg}/test"
    objdir "obj/%{cfg.buildcfg}/test"

    includedirs {
        "include"
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
        "glfw"
    }

    filter "configurations:debug"
        symbols "On"

    filter "configurations:release"
        optimize "On"
        runtime "Release"