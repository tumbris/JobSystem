workspace "JobSystem"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Win64"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    TargetDir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 
    OutputDir = "%{wks.location}/bin/tmp/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "Utility"
    include "JobSystem"
    include "Sandbox"