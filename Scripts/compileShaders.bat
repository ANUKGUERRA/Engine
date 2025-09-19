@echo off
setlocal

:: Define paths relative to script location
set SHADER_SRC=..\Engine\Shaders\GLSL
set SHADER_BIN=..\Engine\Shaders\SPIRV

:: Use VULKAN_SDK if available, or fallback to hardcoded path
set GLSLC="%VULKAN_SDK%\Bin\glslc.exe"
if not exist %GLSLC% (
    set GLSLC="C:\Dev\VulkanSDK\Bin\glslc.exe"
)

:: Compile shaders
%GLSLC% "%SHADER_SRC%\shader.vert" -o "%SHADER_BIN%\shader.vert.spv"
%GLSLC% "%SHADER_SRC%\shader.frag" -o "%SHADER_BIN%\shader.frag.spv"

echo Shader compilation complete.
pause
