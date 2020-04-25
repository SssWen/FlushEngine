workspace "Flush"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	--$(SolutionDir) = E:\Code\FlushEngine\Flush\
	--$(Configurations) = Debug
	--$(Platform) = x64
	--$(ProjectName) = Sandbox

	

-- outputdir = "%{cfg.buildcfg}-%{cfg.system}%{cfg.architecture}"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Flush/vendor/GLFW/include"
include "Flush/vendor/GLFW" -- �����һ��premake

project "Flush"
	location "Flush"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "flushpch.h"
	pchsource "Flush/src/flushpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{prj.name}/src/Flush",
		"%{IncludeDir.GLFW}",
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"		
		systemversion "latest"

		defines
		{
			"FLUSH_PLATFORM_WINDOW",
			"FLUSH_BUILD_DLL"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FLUSH_DEBUG"
		buildoptions {"/MDd"}
		symbols "On"

	filter "configurations:Release"
		defines "FLUSH_RELEASE"
		buildoptions "/MDd"
		optimize "On"

	filter "configurations:Dist"
		defines "FLUSH_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	--targetdir: sets the destination dir for the compiled binary target.
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Flush/vendor/spdlog/include",
		"Flush/src",
		"Flush/src/Flush",
		"Flush/vendor",
	}

	links
	{
		"Flush"
	}

	filter "system:windows"
		cppdialect "C++17"		
		staticruntime "Off"		
        systemversion "latest"

		defines
		{
			"FLUSH_PLATFORM_WINDOW"
		}

	filter "configurations:Debug"
		defines "FLUSH_DEBUG"		
		buildoptions {"/MDd"}
		symbols "On"

	filter "configurations:Release"
		defines "FLUSH_RELEASE"	
		buildoptions "/MDd"	
		optimize "On"

	filter "configurations:Dist"
		defines "FLUSH_DIST"
		optimize "On"