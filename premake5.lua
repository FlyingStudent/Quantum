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
--create Quantum project
project "Quantum"
location "Quantum"
kind "SharedLib"
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
	"%{prj.name}/vendor/spdlog/include",
	"Quantum/src"
}

filter "system:windows"
cppdialect "C++17"
staticruntime "On"
systemversion "latest"

defines {
	"QT_PLATFORM_WINDOWS",
	"QT_BUILD_DLL"
}

postbuildcommands {
	("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/SandBox")
}

filter "configurations:Debug"
defines "QT_DEBUG"
symbols "On"
filter "configurations:Release"
defines "QT_RELEASE"
optimize "On"
filter "configurations:Dist"
defines "QT_DIST"
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
staticruntime "On"
systemversion "latest"

defines {
	"QT_PLATFORM_WINDOWS"
}

filter "configurations:Debug"
defines "QT_DEBUG"
symbols "On"
filter "configurations:Release"
defines "QT_RELEASE"
optimize "On"
filter "configurations:Dist"
defines "QT_DIST"
optimize "On"
