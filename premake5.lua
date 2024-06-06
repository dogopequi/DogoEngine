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
    GLMinclude = "vendor/glm/include"
    IncludeDir = {}
    IncludeDir["glad"] = "Dogo/vendor/glad/include"
    
    include "Dogo/vendor/glad"

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
        "D:/Dev/assimp/Assimp/include"
    }

    libdirs
    {
        "D:/Dev/assimp/Assimp/lib/x64"
    }
    links
    {
        "glad",
		"opengl32.lib",
        "assimp-vc143-mt.lib"
    }

    filter "system:windows"
        system "windows"
        systemversion = "latest"

        defines
        {
            "DG_PLATFORM_WINDOWS",
            "DG_BUILD_STATIC"
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
            "DG_BUILD_SO"
        }

        libdirs
        {
            os.findlib("X11"),
            os.findlib("xcb")
        }

        linkoptions
        {
            "-lxcb",
            "-lX11",
            "-lX11-xcb",
            "-lxkbcommon"
        }

    filter "configurations:Debug"
        defines "DG_BUILD_DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "DG_BUILD_RELEASE"
        optimize "on"
        runtime "Release"

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
        "D:/Dev/assimp/Assimp/include"
    }

    libdirs
    {
        "D:/Dev/assimp/Assimp/lib/x64"
    }

    links
    {
        "assimp-vc143-mt.lib",
        "Dogo"
    }
    
    filter "system:windows"
    system "windows"
        systemversion = "latest"
    
        defines
        {
            "DG_PLATFORM_WINDOWS",
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
        }
    
    filter "configurations:Debug"
        defines "DG_BUILD_DEBUG"
        symbols "on"
        runtime "Debug"
    
    filter "configurations:Release"
        defines "DG_BUILD_RELEASE"
        optimize "on"
        runtime "Release"
