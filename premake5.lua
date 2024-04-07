--create solution
workspace "Quantum"
architecture "x64"

configurations {
	"Debug",
	"Release",
	"Dist"
}
startproject "SandBox"
--path variable
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Quantum/vendor/GLFW/include"
IncludeDir["glad"] = "Quantum/vendor/glad/include"
IncludeDir["ImGui"] = "Quantum/vendor/ImGui"
IncludeDir["glm"] = "Quantum/vendor/glm"
group "Dependencies"
include "Quantum/vendor/GLFW"
include "Quantum/vendor/glad"
include "Quantum/vendor/ImGui"
group ""

--create Quantum project

project "Quantum"
location "Quantum"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")

pchheader "qtpch.h"
pchsource "Quantum/src/qtpch.cpp"

files {
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
	"%{prj.name}/src/**.hpp",
	"%{prj.name}/src/**.c",
	"%{prj.name}/vendor/glm/**.hpp",
	"%{prj.name}/vendor/glm/**.inl"
}
includedirs {
	"%{prj.name}/vendor/spdlog/include",
	"Quantum/src",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.glad}",
	"%{IncludeDir.ImGui}",
	"%{IncludeDir.glm}"
}

--libdirs { "Quantum/vendor/GLFW/lib" }
links {
	"GLFW",
	"ImGui",
	"glad",
	"opengl32.lib"
}
filter "system:windows"
systemversion "latest"

defines {
	"QT_PLATFORM_WINDOWS",
	"QT_BUILD_DLL",
	"GLFW_INCLUDE_NONE",
	"_CRT_SECURE_NO_WARNING"
}

filter "configurations:Debug"
defines "QT_DEBUG"
runtime "Debug"
symbols "on"
filter "configurations:Release"
defines "QT_RELEASE"
runtime "Release"
optimize "on"
filter "configurations:Dist"
defines "QT_DIST"
runtime "Release"
optimize "on"

--create SandBox project
project "SandBox"
location "SandBox"
kind "ConsoleApp"
cppdialect "C++17"
language "C++"
staticruntime "on"

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")

files {
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
	"%{prj.name}/src/**.hpp",
	"%{prj.name}/src/**.c"
}
includedirs {
	"Quantum/vendor/spdlog/include",
	"Quantum/src",
	"%{IncludeDir.glm}"
}

links {
	"Quantum"
}

filter "system:windows"
systemversion "latest"

defines {
	"QT_PLATFORM_WINDOWS"
}

filter "configurations:Debug"
defines "QT_DEBUG"
runtime "Debug"
symbols "on"
filter "configurations:Release"
defines "QT_RELEASE"
runtime "Release"
optimize "on"
filter "configurations:Dist"
defines "QT_DIST"
runtime "Release"
optimize "on"
