project "Engine"
    kind "SharedLib"  -- DLL Project
    language "C++"
    cppdialect "C++20"
    staticruntime "off"
    architecture "x64"

    targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("../bin-int/" .. OutputDir .. "/%{prj.name}")

    local vulkanSDK = os.getenv("VULKAN_SDK")

    files {
        "**.h",
        "**.cpp",
        "../../Dependencies/GLAD/src/glad.c"
    }

    includedirs {
        "src",
        "../../Dependencies/GLFW/include",
        "../../Dependencies/GLAD/include",
        vulkanSDK .. "/include"    
    }

    libdirs {
        "../../Dependencies/GLFW/lib",
        vulkanSDK .. "/lib"
    }

    links {
        "glfw3",      -- GLFW library
        "opengl32",   -- OpenGL  
        "vulkan-1"    -- Vulkan library
    }

    filter "system:windows"
        systemversion "latest"
        defines { "ENGINE_BUILD_DLL", "ENGINE_PLATFORM_WINDOWS"}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
