newoption {
    trigger = "sandbox-mode",
    value = "TYPE",
    description = "Choose Sandbox mode: 'lib' (with Editor) or 'app' (standalone)",
    allowed = {
        { "lib", "Sandbox as StaticLib and Editor as ConsoleApp" },
        { "app", "Sandbox as ConsoleApp, no Editor" }
    },
    default = "lib"
}

workspace "Dogo"
    architecture "x86_64"
    if _OPTIONS["sandbox-mode"] == "app" then
        startproject "Sandbox"
    else
        startproject "Editor"
    end

    configurations
    {
        "Debug",
        "Release"
    }

    outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    STBinclude = "Dogo/vendor/stb_image"
    PHYSXinclude = "Dogo/vendor/PhysX/include"
    PhysXLibDebug = "Dogo/vendor/PhysX/lib/debug/**.lib"
    PhysXLibRelease = "Dogo/vendor/PhysX/lib/release/**.lib"
    GLMinclude = "Dogo/vendor/glm/include"
    ASSIMPinclude = "Dogo/vendor/assimp/include"
    ASSIMPlib = "Dogo/vendor/assimp/lib/x64"
    FreeTypeInclude = "Dogo/vendor/FreeType/include"
    FreeTypeLibDebug = "Dogo/vendor/FreeType/lib/debug/freetype.lib"
    FreeTypeLibRelease = "Dogo/vendor/FreeType/lib/release/freetype.lib"
    IncludeDir = {}
    IncludeDir["glad"] = "Dogo/vendor/glad/include"
    IncludeDir["DogoECS"] = "Dogo/vendor/DogoECS/include"
    IncludeDir["GLFW"] = "Dogo/vendor/GLFW/include"
    
    include "Dogo/vendor/glad"
    include "Dogo/vendor/DogoECS"
    include "Dogo/vendor/GLFW"

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
        "%{IncludeDir.GLFW}",
        ASSIMPinclude,
        PHYSXinclude,
        FreeTypeInclude
    }

    libdirs
    {
        ASSIMPlib
    }
    links
    {
        "DogoECS",
        "glad",
        "GLFW",
		"opengl32.lib",
        "assimp-vc143-mt.lib",
    }

    filter "system:windows"
        system "windows"
        systemversion "latest"

        defines
        {
            "DG_PLATFORM_WINDOWS",
            "DG_BUILD_STATIC",
            "GLFW_STATIC",
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
        systemversion "latest"

        defines
        {
            "DG_PLATFORM_LINUX",
            "DG_BUILD_STATIC",
            "GLFW_STATIC",
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
            PhysXLibDebug,
            FreeTypeLibDebug
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
            PhysXLibRelease,
            FreeTypeLibRelease
        }
        defines
        {
            "NDEBUG"
        }

project "Sandbox"
    location "Sandbox"
    
    local isAppMode = (_OPTIONS["sandbox-mode"] == "app")

    if isAppMode then
        kind "ConsoleApp"
        defines {
            "DG_SANDBOX_MODE_APP"
        }
    else
        kind "StaticLib"
    end
    
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
        
    targetdir ("bin/".. outputDir .. "/%{prj.name}")
    objdir ("bin-int/".. outputDir .. "/%{prj.name}")
    
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    if not isAppMode then
        removefiles {
            "%{prj.name}/src/Entrypoint.cpp"
        }
    end
    includedirs {
        "Dogo/src",
        STBinclude,
        GLMinclude,
        "%{IncludeDir.glad}",
        "%{IncludeDir.DogoECS}",
        "%{IncludeDir.GLFW}",
        PHYSXinclude
    }
    
    links {
        "Dogo",
        "glad",
        "GLFW",
        "DogoECS"
    }
    
    filter "system:windows"
    system "windows"
        systemversion "latest"
    
        defines
        {
            "DG_PLATFORM_WINDOWS",
        }

    filter "system:linux"
        system "linux"
        systemversion "latest"
    
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
            PhysXLibDebug
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
            PhysXLibRelease
        }
        defines
        {
            "NDEBUG"
        }
if _OPTIONS["sandbox-mode"] ~= "app" then
    project "Editor"
        location "Editor"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
                
        targetdir ("bin/".. outputDir .. "/%{prj.name}")
        objdir ("bin-int/".. outputDir .. "/%{prj.name}")
            
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
            
        includedirs {
            "Dogo/src",
            "Sandbox/src",
            STBinclude,
            GLMinclude,
            "%{IncludeDir.glad}",
            "%{IncludeDir.DogoECS}",
            "%{IncludeDir.GLFW}",
            PHYSXinclude
        }
            
        links {
            "Sandbox"
        }
    
        filter "system:windows"
        system "windows"
            systemversion "latest"
    
            defines
            {
                "DG_PLATFORM_WINDOWS",
            }

        filter "system:linux"
            system "linux"
            systemversion "latest"
    
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
        end