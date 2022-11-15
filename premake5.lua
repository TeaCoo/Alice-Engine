workspace "Alice"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		symbols "On"

	filter "configurations:Release"
		defines "ALICE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ALICE_DIST"
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
		"%{prj.name}/src"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ALICE_PLATFORM_WINDOWS",
			"ALICE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "ALICE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ALICE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ALICE_DIST"
		optimize "On"

