project "GLFW"
kind "StaticLib"
language "C"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
  "include/GLFW/glfw3.h",
  "include/GLFW/glfw3native.h",
  "src/glfw_config.h",
  "src/context.c",
  "src/init.c",
  "src/input.c",
  "src/monitor.c",
  "src/vulkan.c",
  "src/mappings.h",
  "src/internal.h",
  "src/platform.h",
  "src/platform.c",
  "src/null_init.c",
  "src/null_joystick.c",
  "src/null_monitor.c",
  "src/null_platform.h",
  "src/null_window.c",
  "src/window.c",
  "src/egl_context.c",
  "src/osmesa_context.c"
}

filter "system:macosx"
systemversion "12"

files {
  "src/cocoa_init.m",
  "src/cocoa_joystick.m",
  "src/cocoa_joystick.h",
  "src/cocoa_monitor.m",
  "src/cocoa_time.c",
  "src/cocoa_time.h",
  "src/cocoa_window.m",
  "src/cocoa_platform.h",
  "src/nsgl_context.m",
  "src/posix_module.c",
  "src/posix_thread.c",
}

defines {
  "_GLFW_COCOA"
}

filter "system:windows"
systemversion "10"

files {
  "win32_init.c",
  "win32_joystick.c",
  "win32_module.c",
  "win32_monitor.c",
  "win32_thread.c",
  "win32_time.c",
  "win32_window.c",
  "wgl_context.c",
  "egl_context.c",
  "osmesa_context.c"
}

defines {
  "_GLFW_WIN32",
  "_CRT_SECURE_NO_WARNINGS"
}

filter "system:linux"
systemversion ""

files {
  "linux_joystick.c",
  "linux_joystick.h",
  "wl_init.c",
  "wl_monitor.c",
  "wl_platform.h",
  "wl_window.c",
  "x11_init.c",
  "x11_monitor.c",
  "x11_platform.h",
  "x11_window.c",
  "xkb_unicode.c",
  "xkb_unicode.h"
}

filter "configurations:Debug"
runtime "Debug"
symbols "on"

filter "configurations:Release"
runtime "Release"
optimize "on"
