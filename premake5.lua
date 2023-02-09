workspace "Wukong"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Wukong"
	location "Wukong"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir )
	objdir ("bin-int/" .. outputdir )

	pchheader "Wupch.h"
	pchsource "%{prj.name}/src/Wupch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/3rdparty/spdlog/include"
	}

	links
	{

		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{

		}


	filter "configurations:Debug"
		defines "WU_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WU_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "WU_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir )
	objdir ("bin-int/" .. outputdir )

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

	}

	includedirs
	{
		"Wukong/3rdparty/spdlog/include",
		"Wukong/src"
	}

	links
	{
		"Wukong"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "WU_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WU_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "WU_DIST"
		runtime "Release"
		optimize "On"

		
