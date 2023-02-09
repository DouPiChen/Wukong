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

include "Wukong/3rdparty"


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

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/3rdparty/spdlog/include",
		"%{prj.name}/3rdparty/glfw/include",
		"%{prj.name}/3rdparty/glad/include",
		"%{prj.name}/3rdparty/imgui"
	}

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		systemversion "latest"
		defines "WU_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		systemversion "latest"
		defines "WU_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		systemversion "latest"
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
		"Wukong/src",
		"Wukong/3rdparty"
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
			"WU_PLATFORM_WINDOWS",
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

		
