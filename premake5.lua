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
IncludeDir["glm"] = "Granola/vendor/glm"
IncludeDir["stb_image"] = "Granola/vendor/stb_image"

group "Dependencies"
	include "Granola/vendor/GLFW"
	include "Granola/vendor/Glad"
	include "Granola/vendor/imgui"
group ""

-- Granola project
project "Granola"
	location "Granola"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
staticruntime "on"

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
		"%{prj.name}/ClassDiagram.cd",
		-- glm
		"Granola/vendor/glm/**.hpp",
		"Granola/vendor/glm/**.inl",
		-- stb_image
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	includedirs
	{
		-- TODO include dir should work
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
		"{IncludeDir.ImGui}",
		-- glm
		"%{prj.name}/vendor/glm",
		"{IncludeDir.glm}",
		-- stb_image
		"%{prj.name}/vendor/stb_image",
		"{IncludeDir.stb_image}"
		
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

	defines { "IMGUI_API=__declspec(dllexport)" }

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"GRL_PLATFORM_WINDOWS",
			"GRL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines 
		{
			"GRL_DEBUG",
			"GRL_ENABLE_ASSERTS",
			"GRL_PROFILE",
		}
		runtime "Debug"
		symbols "on"
		buildoptions "/external:W0"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		runtime "Release"
		optimize "on"
		buildoptions "/W4"

	filter "configurations:Dist"
		defines "GRL_DIST"
		runtime "Release"
		optimize "on"

-- Sandbox project
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir ..  "/%{prj.name}")
	objdir ("bin-int/" .. outputdir ..  "/%{prj.name}")
	files
	{
		-- source files
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		-- glm
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		--source files
		"Granola/vendor/spdlog/include",
		"Granola/src",
		"%{prj.name}/src",
		-- glm
		"Granola/vendor/glm",
		"{IncludeDir.glm}"
	}

	links
	{
		"Granola"
	}

	defines { "IMGUI_API=__declspec(dllimport)" }

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"GRL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GRL_DEBUG"
		runtime "Debug"
		symbols "on"
		buildoptions "/external:W0"

	filter "configurations:Release"
		defines "GRL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GRL_DIST"
		runtime "Release"
		optimize "on"

