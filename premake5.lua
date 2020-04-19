workspace "Flush"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Flush"
	location "Flush"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"		
		systemversion "10.0.17763.0"

		defines
		{
			"FLUSH_PLATFORM_WINDOWS",
			"FLUSH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FLUSH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FLUSH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FLUSH_DIST"
		optimize "On"

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
		"Flush/vendor/spdlog/include",
		"Flush/src"
	}

	links
	{
		"Flush"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"        
        systemversion "10.0.17763.0"

		defines
		{
			"FLUSH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FLUSH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FLUSH_DIST"
		optimize "On"