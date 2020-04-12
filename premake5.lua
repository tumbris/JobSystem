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

    OutputDir = "%{wks.location}/tmp/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    TargetDir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

    include "Utility"
    include "JobSystem"
    include "Sandbox"