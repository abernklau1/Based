#include "Based/Core/Input.h"
#include "bsdpch.h"

#ifdef BSD_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsInput.h"
#elif BSD_PLATFORM_MAC
    #include "Platform/MacOSX/MacInput.h"
#endif

namespace Based
{
    Scope<Input> Input::s_Instance = Input::Create();

    Scope<Input> Input::Create()
    {
#ifdef BSD_PLATFORM_WINDOWS
        return CreateScope<WindowsInput>();
#elif BSD_PLATFORM_MAC
        return CreateScope<MacInput>();
#else
        BSD_CORE_ASSERT(false, "Unknown platform");
        return nullptr;
#endif
    }
} // namespace Based
