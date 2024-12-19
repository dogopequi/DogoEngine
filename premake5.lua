workspace "Dogo"
    architecture "x86_64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

    outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    STBinclude = "vendor/stb_image"
    PHYSXinclude = "D:/Dev/DogoEngine/vendor/PhysX/include"
    TOLinclude = "Dogo/vendor/tinyobjloader/include"
    GLMinclude = "vendor/glm/include"
    ASSIMPinclude = "vendor/assimp/include"
    ASSIMPlib = "vendor/assimp/lib/x64"
    IncludeDir = {}
    IncludeDir["glad"] = "Dogo/vendor/glad/include"
    IncludeDir["DogoECS"] = "Dogo/vendor/DogoECS/include"
    
    include "Dogo/vendor/glad"
    include "Dogo/vendor/DogoECS"

project "Dogo"
    location "Dogo"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/".. outputDir .. "/%{prj.name}")
    objdir ("bin-int/".. outputDir .. "/%{prj.name}")

    pchheader "dgpch.h"
    pchsource "Dogo/src/dgpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        STBinclude,
        GLMinclude,
        "%{IncludeDir.glad}",
        "%{IncludeDir.DogoECS}",
        ASSIMPinclude,
        TOLinclude,
        PHYSXinclude
    }

    libdirs
    {
        ASSIMPlib
    }
    links
    {
        "DogoECS",
        "glad",
		"opengl32.lib",
        "assimp-vc143-mt.lib",
    }

    filter "system:windows"
        system "windows"
        systemversion = "latest"

        defines
        {
            "DG_PLATFORM_WINDOWS",
            "DG_BUILD_STATIC",
            "ASSIMP_STATIC"
        }

        links
        {
            "d3d11.lib",
            "dxgi.lib",
            "dxguid.lib",
            "uuid.lib",
            "kernel32.lib",
            "user32.lib",
            "comdlg32.lib",
            "advapi32.lib",
            "shell32.lib",
            "ole32.lib",
            "oleaut32.lib",
            "D3DCompiler.lib"
        }

    filter "system:linux"
        system "linux"
        systemversion = "latest"

        defines
        {
            "DG_PLATFORM_LINUX",
            "DG_BUILD_STATIC",
            "ASSIMP_STATIC"
        }

        libdirs
        {
            os.findlib("X11"),
        }

        links
        {
            "GL",
            "X11"
        }

       buildoptions
       {
           "-v"  -- Enable verbose output
       }
    

    filter "configurations:Debug"
        defines "DG_BUILD_DEBUG"
        symbols "on"
        runtime "Debug"
        links
        {
            "D:/Dev/DogoEngine/vendor/PhysX/lib/debug/**.lib"
        }
        defines
        {
            "_DEBUG"
        }

    filter "configurations:Release"
        defines "DG_BUILD_RELEASE"
        optimize "on"
        runtime "Release"
        links
        {
            "D:/Dev/DogoEngine/vendor/PhysX/lib/release/**.lib"
        }
        defines
        {
            "NDEBUG"
        }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/".. outputDir .. "/%{prj.name}")
    objdir ("bin-int/".. outputDir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Dogo/src",
        STBinclude,
        GLMinclude,
        "%{IncludeDir.glad}",
        "%{IncludeDir.DogoECS}",
        PHYSXinclude
    }


    links
    {
        "Dogo",
        "glad",
        "DogoECS"
    }
    
    filter "system:windows"
    system "windows"
        systemversion = "latest"
    
        defines
        {
            "DG_PLATFORM_WINDOWS",
        }

    filter "system:linux"
        system "linux"
        systemversion = "latest"
    
        defines
        {
            "DG_PLATFORM_LINUX",
        }

        libdirs
        {
            os.findlib("X11"),
        }

        links
        {
            "GL",
            "X11"
        }

    
    filter "configurations:Debug"
        defines "DG_BUILD_DEBUG"
        symbols "on"
        runtime "Debug"
        links
        {
            "D:/Dev/DogoEngine/vendor/PhysX/lib/debug/**.lib"
        }
        defines
        {
            "_DEBUG"
        }
    
    filter "configurations:Release"
        defines "DG_BUILD_RELEASE"
        optimize "on"
        runtime "Release"
        links
        {
            "D:/Dev/DogoEngine/vendor/PhysX/lib/release/**.lib"
        }
        defines
        {
            "NDEBUG"
        }
