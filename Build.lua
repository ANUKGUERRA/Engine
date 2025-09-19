workspace "Engine"
    startproject "Editor"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}/%{cfg.architecture}"
    local vulkanSDK = os.getenv("VULKAN_SDK")


    project "Engine"
        location "Engine"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"

        targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
        objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs {
            "%{prj.name}/src",
            "Dependencies/GLFW/include",
            "Dependencies/GLM/include",
            vulkanSDK .. "/include"  
        }

        libdirs {
            "Dependencies/GLFW/lib",
            vulkanSDK .. "/lib"
        }

        links 
        {
            "glfw3",
            "vulkan-1"
        }

        filter "system:windows"
            systemversion "latest"

            defines {"ENGINE_PLATFORM_WINDOWS"}

        filter "configurations:Debug"
            defines "Engine_Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "Engine_Release"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "Engine_Dist"
            runtime "Release"
            optimize "on"



    project "Editor"
        location "Editor"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"

        targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
        objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs 
        {
            "%{prj.name}/src",
            "Dependencies/GLM/include",
            "Engine/src"   
        }

        links 
        {
            "Engine"
        }

        filter "system:windows"
            systemversion "latest"

            defines {"ENGINE_PLATFORM_WINDOWS"}

        filter "configurations:Debug"
            defines "Engine_Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "Engine_Release"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "Engine_Dist"
            runtime "Release"
            optimize "on"

