project "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files
   {
       "src/**.h",
       "src/**.cpp"
   }

   includedirs
   {
      "src",
      "Platform/GUI",

      "../Dependencies/imgui",
      "../Dependencies/GLFW/include",
      "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}"
   }

   links
   {
       "ImGui",
       "../Dependencies/GLFW/lib/glfw3",

       "%{Library.Vulkan}",
   }

   targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      defines { "WINDOWS_OS" }
      systemversion "latest"
      buildoptions { "/utf-8" }

   filter "system:linux"
      defines { "LINUX_OS" }
      systemversion "latest"
      buildoptions { "/utf-8" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      defines { "DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"