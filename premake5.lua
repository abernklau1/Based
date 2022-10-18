workspace "Based"
architecture "ARM64"
startproject "Sandbox"

configurations {
  "Debug",
  "release",
  "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directiory)
-- IncludeDir = {}
-- IncludeDir["GLFW"] = "Based/vendor/GLFW/include"

include "Based/vendor/GLFW"
include "Based/vendor/Glad"
include "Based/vendor/imgui"
-- include "Based/vendor/glm"

group "Dependencies"
include "Based/vendor/GLFW"
include "Based/vendor/Glad"
include "Based/vendor/imgui"
-- include "Based/vendor/glm"
group ""

project "Based"
location "Based"
kind "SharedLib"
language "C++"

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

filter "system:macosx"
cppdialect "C++17"
staticruntime "On"
systemversion "12"

defines {
  "BSD_PLATFORM_MAC",
  "BSD_BUILD_SHRD_LIB",
  "GLFW_INCLUDE_NONE"
}

postbuildcommands {
  ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
}

filter "configurations:Debug"
defines "BSD_DEBUG"
-- buildoptions "/MDd"
symbols "On"

filter "configurations:Release"
defines "BSD_RELEASE"
-- buildoptions "/MD"
symbols "On"

filter "configurations:Dist"
defines "BSD_DIST"
-- buildoptions "/MD"
symbols "On"

project "Sandbox"
location "Sandbox"
kind "ConsoleApp"
language "C++"

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
cppdialect "C++17"
staticruntime "On"
systemversion "12"

defines {
  "BSD_PLATFORM_MAC",
}

filter "configurations:Debug"
defines "BSD_DEBUG"
-- buildoptions "/MDd"
symbols "On"

filter "configurations:Release"
defines "BSD_RELEASE"
-- buildoptions "/MD"
symbols "On"

filter "configurations:Dist"
defines "BSD_DIST"
-- buildoptions "/MD"
symbols "On"
