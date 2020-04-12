project "JobSystem"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    objdir (OutputDir .. "/%{prj.name}")
    targetdir (TargetDir)

    files 
    {
        "**.cpp"
        , "**.h"
    }

    includedirs
    {
        "%{wks.location}"
    }

    links 
    {
        "Utility"
    }

    filter {"configurations:Debug"}
        defines 
        {
            "DEBUG"
        }
        symbols "On"
        runtime "Debug"

    filter {"configurations:Release"}
        defines 
        {
            "NDEBUG"
            , "RELEASE"
        }
        optimize "On"
        runtime "Release"

    filter {"platforms:Win64"}
        systemversion "latest"

        defines
        {
            "JOBSYSTEM_EXPORTS",
        }