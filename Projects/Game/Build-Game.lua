project "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    architecture "x64"


    targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../bin-int/" .. OutputDir .. "/%{prj.name}")

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
        "{COPY} ../bin/" .. OutputDir .. "/Engine/Engine.dll %{cfg.targetdir}"
    }



    filter "system:windows"
        systemversion "latest"
        defines {"ENGINE_PLATFORM_WINDOWS"}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"


