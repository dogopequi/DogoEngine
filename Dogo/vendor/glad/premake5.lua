project "glad"
    kind "StaticLib"
    language "C"
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
    
    filter "system:windows"
        systemversion "latest"

        files
        {
            "include/glad/glad.h",
            "include/KHR/khrplatform.h",
            "src/glad.c"
        }

    filter "system:linux"
        systemversion "latest"

        files
        {
            "include/glad/gl.h",
            "include/glad/glx.h",
            "include/KHR/khrplatform.h",
            "src/gl.c",
            "src/glx.c"
        }
