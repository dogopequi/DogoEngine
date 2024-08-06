project "DogoECS"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/" .. outputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	includedirs
	{
		"include"
	}

    filter "configurations:Debug"
        defines "DG_BUILD_DEBUG"
        symbols "on"
        runtime "Debug"

    filter "configurations:Release"
        defines "DG_BUILD_RELEASE"
        optimize "on"
        runtime "Release"

    files
    {
        "include/Components.h",
        "include/DG_Component.h",
        "include/dgpch.h",
        "include/Entity.h",
        "include/UUID.h",
        "src/DG_Component.cpp",
        "src/Entity.cpp"
    }
    
    filter "system:windows"
        systemversion "latest"


    filter "system:linux"
        systemversion "latest"
