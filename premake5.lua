-- Granola premake file
workspace "Granola"
	architecture "x64"
	--startupproject "Sandbox"
	-- Generate the CMake file
	--cmakefile "CMakeLists.txt"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include OpenGL, GLFW, Glad and ImGui
IncludeDir = {}
IncludeDir["GLFW"] = "Granola/vendor/GLFW/include"
IncludeDir["Glad"] = "Granola/vendor/Glad/include"
IncludeDir["ImGui"] = "Granola/vendor/imgui"

group "Dependencies"
	include "Granola/vendor/GLFW"
	include "Granola/vendor/Glad"
	include "Granola/vendor/imgui"
group ""

-- Granola project
project "Granola"
	location "Granola"
	kind "SharedLib"
	language "C++"
staticruntime "off"

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
		"{IncludeDir.Glad}",
		-- ImGui
		"%{prj.name}/vendor/imgui",
		"{IncludeDir.ImGui}"
	}

	links
	{
		--vendor
		--GLFW
		"GLFW",
		"opengl32.lib",
		--Glad
		"Glad",
		--ImGui
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		defines
		{
			"GRL_PLATFORM_WINDOWS",
			"GRL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			-- copy granola.dll to Sandbox/bin/$(Configuration)/Sandbox or create new folder
			-- solved by just splitting path
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines 
		{
			"GRL_DEBUG",
			"GRL_ENABLE_ASSERTS",
			"GRL_PROFILE",
		}
		runtime "Debug"
		symbols "On"
		buildoptions "/external:W0"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GRL_DIST"
		runtime "Release"
		optimize "On"

-- Sandbox project
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "latest"
		defines
		{
			"GRL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GRL_DEBUG"
		runtime "Debug"
		symbols "On"
		buildoptions "/external:W0"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GRL_DIST"
		runtime "Release"
		optimize "On"

