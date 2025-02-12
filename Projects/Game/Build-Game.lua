project "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    architecture "x86_64"


    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "../Engine/src",
        "../../Dependencies/GLFW/include"
    }

    libdirs {
        "../../Dependencies/GLFW/lib",
    }
    links {
        "Engine",
        "glfw3"
    }

    postbuildcommands {
        "{COPY} ../Engine/bin/" .. OutputDir .. "/Engine/Engine.dll %{cfg.targetdir}"
    }

    defines {"ENGINE_PLATFORM_WINDOWS"}


    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"


