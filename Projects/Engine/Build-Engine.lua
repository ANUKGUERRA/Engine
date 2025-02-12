project "Engine"
    kind "SharedLib"  -- DLL Project
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    architecture "x86_64"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files {
        "**.h",
        "**.cpp",
    }

    includedirs {
        "src",
        "../../Dependencies/GLFW/include"
    }

    libdirs {
        "../../Dependencies/GLFW/lib"  
    }
    links {
        "glfw3",      -- GLFW library
        "opengl32",   -- OpenGL
        "gdi32",      -- Windows graphics device interface
        "user32",     -- Windows user interface
        "shell32"     
    }

    defines { "ENGINE_BUILD_DLL", "ENGINE_PLATFORM_WINDOWS"}


    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
