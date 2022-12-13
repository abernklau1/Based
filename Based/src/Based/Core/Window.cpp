#include "bsdpch.h"
#include "Based/Core/Window.h"

#ifdef BSD_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#elif defined(BSD_PLATFORM_MAC)
#include "Platform/MacOSX/MacWindow.h"
#endif

namespace Based {
Scope<Window> Window::Create(const WindowProps& props) {
  #ifdef BSD_PLATFORM_WINDOWS
  return CreateScope<WindowsWindow>(props);
  #elif BSD_PLATFORM_MAC
  return CreateScope<MacWindow>(props);
  #else
  BSD_CORE_ASSERT(false, "Unknown platform");
  return nullptr;
  #endif
}
}

