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
      systemversion "latest"
      buildoptions { "/utf-8" }

   filter "configurations:Debug"
      defines { "W_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "W_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      defines { "W_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"