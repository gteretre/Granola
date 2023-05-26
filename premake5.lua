-- Granola premake file
workspace "Granola"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include OpenGL, GLFW
IncludeDir = {}
IncludeDir["GLFW"] = "Granola/vendor/GLFW/include"
IncludeDir["Glad"] = "Granola/vendor/Glad/include"

include "Granola/vendor/GLFW"
include "Granola/vendor/Glad"

-- Granola project
project "Granola"
	location "Granola"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir ..  "/%{prj.name}")
	objdir ("bin-int/" .. outputdir ..  "/%{prj.name}")

	pchheader "grlpch.h"
	pchsource "Granola/src/grlpch.cpp"

	files
	{
		-- source files
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/cpp.hint",
		"%{prj.name}/ClassDiagram.cd"
	}

	includedirs
	{
		-- source files
		"%{prj.name}/src",
		-- vendor
		-- spdlog
		"%{prj.name}/vendor/spdlog/include",
		-- GLFW
		"%{prj.name}/vendor/GLFW/include",
		"{IncludeDir.GLFW}",
		-- Glad
		"%{prj.name}/vendor/Glad/include",
		"{IncludeDir.Glad}"
	}

	links
	{
		--vendor
		--GLFW
		"GLFW",
		"opengl32.lib",
		--Glad
		"Glad"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"GRL_PLATFORM_WINDOWS",
			"GRL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines 
		{
			"GRL_DEBUG",
			"GRL_ENABLE_ASSERTS",
			"GRL_PROFILE",
		}
		symbols "On"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRL_DIST"
		optimize "On"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"

	filter {"system:windows", "configurations:Debug"}
		buildoptions "/external:W0 /fsanitize=address"


-- Sandbox project
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir ..  "/%{prj.name}")
	objdir ("bin-int/" .. outputdir ..  "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Granola/vendor/spdlog/include",
		"Granola/src",
		"%{prj.name}/src"
	}

	links
	{
		"Granola"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"GRL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GRL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GRL_DIST"
		buildoptions "/MD"
		optimize "On"

