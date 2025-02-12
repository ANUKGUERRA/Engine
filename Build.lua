workspace "Engine"
    configurations{"Debug", "Release"}
    startproject "Editor"

    OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"


include "Projects/Engine/Build-Engine.lua"
include "Projects/Editor/Build-Editor.lua"
include "Projects/Game/Build-Game.lua"