project "DogoECS"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    targetdir ("bin/".. outputDir .. "/%{prj.name}")
    objdir ("bin-int/".. outputDir .. "/%{prj.name}")

	includedirs
	{
		"include"
	}
    
    files
    {
        "include/DG_Component.h",
        "include/dgpch.h",
        "include/Entity.h",
        "include/UUID.h",
        "include/DogoECS.h",
        "src/DG_Component.cpp",
        "src/Entity.cpp"
    }

    filter "configurations:Debug"
        defines "DG_BUILD_DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "DG_BUILD_RELEASE"
        optimize "on"
        runtime "Release"
    
    filter "system:windows"
        system "windows"
        systemversion "latest"


    filter "system:linux"
        system "linux"
        systemversion "latest"

        buildoptions
        {
            "-v"
        }
