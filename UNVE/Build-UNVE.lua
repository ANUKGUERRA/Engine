project "UNVE"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   includedirs
   {
      "../Dependencies/imgui",
      "../Dependencies/GLFW/include",
      "../Engine/src",
      "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",
   }

   links
   {
      "Engine"
   }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

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
      kind "WindowedApp"
      runtime "Release"
      optimize "On"
      symbols "Off"
