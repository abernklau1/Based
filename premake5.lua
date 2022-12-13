workspace "Based"
architecture "ARM64"
startproject "Sandbox"

configurations {
  "Debug",
  "Release",
  "Dist"
}

flags {
  "MultiProcessorCompile"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Based/vendor/GLFW/include"
IncludeDir["Glad"] = "Based/vendor/Glad/include"
IncludeDir["ImGui"] = "Based/vendor/imgui"
IncludeDir["glm"] = "Based/vendor/glm"
IncludeDir["stb_img"] = "Based/vendor/stb_img"

group "Dependencies"
include "Based/vendor/GLFW"
include "Based/vendor/Glad"
include "Based/vendor/imgui"
group ""

project "Based"
location "Based"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "%{prj.name}/src/bsdpch.h"

files {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp",
  "%{prj.name}/vendor/glm/glm/**.hpp",
  "%{prj.name}/vendor/glm/glm/**.inl",
  "%{prj.name}/vendor/stb_img/stb_image.h",
  "%{prj.name}/vendor/stb_img/stb_image.cpp",
}


includedirs {
  "%{prj.name}/src",
  "%{prj.name}/vendor/spdlog/include",
  "%{IncludeDir.GLFW}",
	"%{IncludeDir.Glad}",
	"%{IncludeDir.ImGui}",
	"%{IncludeDir.glm}",
  "%{prj.name}/vendor/stb_img"
}

links {
  "Glad",
  "GLFW",
  "imgui",
}

defines {
  "GLFW_INCLUDE_NONE",
  "_CRT_SECURE_NO_WARNINGS",
  "GLM_FORCE_CTOR_INIT",
}

filter "system:macosx"
systemversion "12"

links {
  "glfw",
  "Cocoa.framework",
  "OpenGL.framework",
  "IOKit.framework",

}

defines {
  "BSD_PLATFORM_MAC",
}

filter "system:windows"
systemversion "latest"

links {
  "opengl32.lib"
}

defines {
  "BSD_PLATFORM_WINDOWS",
}

filter "configurations:Debug"
defines "BSD_DEBUG"
runtime "Debug"
symbols "on"

filter "configurations:Release"
defines "BSD_RELEASE"
runtime "Release"
optimize "on"

filter "configurations:Dist"
defines "BSD_DIST"
runtime "Release"
optimize "on"

project "Sandbox"
location "Sandbox"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
}

includedirs {
  "Based/src",
  "Based/vendor/spdlog/include",
  "Based/vendor",
  "Based/vendor/glm",
  "Sandbox/src"
}

links {
  "Based",
}

filter "system:macosx"
systemversion "12"
links {
  "Glad",
  "GLFW",
  "glfw",
  "Cocoa.framework",
  "OpenGL.framework",
  "IOKit.framework",
  "imgui",
}

defines {
  "BSD_PLATFORM_MAC",
}

filter "configurations:Debug"
defines "BSD_DEBUG"
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines "BSD_RELEASE"
runtime "Release"
optimize "On"

filter "configurations:Dist"
defines "BSD_DIST"
runtime "Release"
optimize "On"
