--create solution
workspace "Quantum"
architecture "x64"

configurations {
	"Debug",
	"Release",
	"Dist"
}
--path variable
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Quantum/vendor/GLFW/include"
IncludeDir["glad"] = "Quantum/vendor/glad/include"
IncludeDir["ImGui"] = "Quantum/vendor/ImGui"
include "Quantum/vendor/GLFW"
include "Quantum/vendor/glad"
include "Quantum/vendor/ImGui"
--create Quantum project
project "Quantum"
location "Quantum"
kind "SharedLib"
language "C++"

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")

pchheader "qtpch.h"
pchsource "Quantum/src/qtpch.cpp"

files {
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
	"%{prj.name}/src/**.hpp",
	"%{prj.name}/src/**.c"
}
includedirs {
	"%{prj.name}/vendor/spdlog/include",
	"Quantum/src",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.glad}",
	"%{IncludeDir.ImGui}"
}

--libdirs { "Quantum/vendor/GLFW/lib" }
links {
	"GLFW",
	"ImGui",
	"glad",
	"opengl32.lib"
}
filter "system:windows"
cppdialect "C++17"
staticruntime "off"
systemversion "latest"

defines {
	"QT_PLATFORM_WINDOWS",
	"QT_BUILD_DLL",
	"GLFW_INCLUDE_NONE"
}

postbuildcommands {
	("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/SandBox")
}

filter "configurations:Debug"
defines "QT_DEBUG"
buildoptions "/MDd"
symbols "On"
filter "configurations:Release"
defines "QT_RELEASE"
buildoptions "/MDd"
optimize "On"
filter "configurations:Dist"
defines "QT_DIST"
buildoptions "/MDd"
optimize "On"

--create SandBox project
project "SandBox"
location "SandBox"
kind "ConsoleApp"
language "C++"

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
	"Quantum/src"
}

links {
	"Quantum"
}

filter "system:windows"
cppdialect "C++17"
staticruntime "off"
systemversion "latest"

defines {
	"QT_PLATFORM_WINDOWS"
}

filter "configurations:Debug"
defines "QT_DEBUG"
buildoptions "/MDd"
symbols "On"
filter "configurations:Release"
defines "QT_RELEASE"
buildoptions "/MDd"
optimize "On"
filter "configurations:Dist"
defines "QT_DIST"
buildoptions "/MDd"
optimize "On"
