workspace "Based"
architecture "ARM64"
startproject "Sandbox"

configurations {
  "Debug",
  "release",
  "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Based"
location "Based"
kind "SharedLib"
language "C++"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
}

includedirs {
  "%{prj.name}/src",
  "%{prj.name}/vendor/spdlog/include"
}

filter "system:macosx"
cppdialect "C++17"
staticruntime "On"
systemversion "12"

defines {
  "BSD_PLATFORM_MAC",
  "BSD_BUILD_SHRD_LIB"
}

postbuildcommands {
  ("{COPY} %{cfg.buildtarget.relpath} ..bin/" .. outputdir .. "/Sandbox")
}

filter "configurations:Debug"
defines "BSD_DEBUG"
symbols "On"

filter "configurations:Release"
defines "BSD_RELEASE"
symbols "On"

filter "configurations:Dist"
defines "BSD_DIST"
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
  "Based/vendor/spdlog/include"
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
symbols "On"

filter "configurations:Release"
defines "BSD_RELEASE"
symbols "On"

filter "configurations:Dist"
defines "BSD_DIST"
symbols "On"
