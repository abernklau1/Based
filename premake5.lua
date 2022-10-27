workspace "Based"
architecture "ARM64"
startproject "Sandbox"

configurations {
  "Debug",
  "release",
  "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Based/vendor/GLFW"
include "Based/vendor/Glad"
include "Based/vendor/imgui"

-- group "Dependencies"
-- include "Based/vendor/GLFW"
-- include "Based/vendor/Glad"
-- include "Based/vendor/imgui"
-- group ""

project "Based"
location "Based"
-- kind "SharedLib"
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
}


includedirs {
  "%{prj.name}/src",
  "%{prj.name}/vendor/spdlog/include",
  "%{prj.name}/vendor/GLFW/include",
  "%{prj.name}/vendor/Glad/include",
  "%{prj.name}/vendor/imgui",
  "%{prj.name}/vendor/glm"
}

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
  "GLFW_INCLUDE_NONE",
  "_CRT_SECURE_NO_WARNINGS",
  "GLM_FORCE_CTOR_INIT"
}

filter "system:macosx"
systemversion "12"
kind "SharedLib"
staticruntime "off"

defines {
  "BSD_PLATFORM_MAC",
  "BSD_BUILD_SHRD_LIB",
}

filter "system:windows"
systemversion "latest"
kind "StaticLib"

defines {
  "BSD_PLATFORM_WINDOWS",
  "BSD_BUILD_SL"
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

links {
  "Based"
}

files {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
}

includedirs {
  "Based/src",
  "Based/vendor/spdlog/include",
  "Based/vendor",
  "Based/vendor/glm"
}

filter "system:macosx"
systemversion "12"
staticruntime "off"

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
