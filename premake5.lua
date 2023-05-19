workspace "Granola"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
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
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GRL_PLATFORM_WINDOWS",
			"GRL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "GRL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRL_DIST"
		optimize "On"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"



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
		symbols "On"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRL_DIST"
		optimize "On"

