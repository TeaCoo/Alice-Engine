workspace "Alice"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
includeDir = {}
includeDir["GLFW"] = "Alice/extern/GLFW/include"
includeDir["Glad"] = "Alice/extern/Glad/include"

include "Alice/extern/GLFW"
include "Alice/extern/Glad"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Alice/extern/spdlog/include",
		"Alice/src"
	}

	links
	{
		"Alice"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ALICE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ALICE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ALICE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ALICE_DIST"
		buildoptions "/MD"
		optimize "On"

project "Alice"
	location "Alice"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "Alice/src/pch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/extern/spdlog/include",
		"%{prj.name}/src",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ALICE_PLATFORM_WINDOWS",
			"ALICE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "ALICE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ALICE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "ALICE_DIST"
		buildoptions "/MD"
		optimize "On"

