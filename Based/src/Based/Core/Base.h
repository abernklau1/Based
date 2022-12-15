#pragma once

#include <memory>

#ifdef _WIN32
    // Windows x64/x86
    #ifdef _WIN64
        // Windows x64
        #define BSD_PLATFORM_WINDOWS
    #else
        // Windows x86
        #error "x86 is not currently supported by the Based Engine"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /* TARGET_OS_MAC exists on all Apple platforms
       so all Apple platforms must be checked in this order
       to ensure that user is running on MAC and not
       another Apple platform
    */
    #if TARGET_OS_IPHONE == 1
        #error "IOS simulator is not currently supported by the Based Engine"
    #elif TARGET_OS_IPHONE == 1
        #define BSD_PLATFORM_IOS
        #error "IOS is not currenly supported"
    #elif TARGET_OS_MAC == 1
        #define BSD_PLATFORM_MACOS
    #else
        #error "Unknown Apple platform"
    #endif
/* __ANDROID__ must be checked before __linux__,
   due to Android's Linux based kernel
   it defines __linux__
*/
#elif defined(__ANDROID__)
    #define BSD_PLATFORM_ANDROID
    #error "Android is not currently supported by the Based Engine"
#elif defined(__linux__)
    #define BSD_PLATFORM_LINUX
    #error "Linux is not currently supported by the Based Engine"
#else
    #error "Uknown platform"
#endif

// DLL Support
#ifdef BSD_PLATFORM_WINDOWS
    #if BSD_DYNAMIC_LINK
        #ifdef BSD_BUILD_DLL
            #define BASED_API __declspec(dllexport)
        #else
            #define Based_API __declspec(dllimport)
        #endif
    #else
        #define BASED_API
    #endif
#endif

#ifdef BSD_DEBUG
    #if defined(BSD_PLATFORM_WINDOWS)
        #define BSD_DEBUG_BREAK() __debugbreak()
    #elif defined(BSD_PLATFORM_LINUX) || defined(BSD_PLATFORM_MACOS)
        #include <signal.h>
        #define BSD_DEBUG_BREAK() raise(SIGTRAP)
    #else
        #error "Platform has yet to support debugbreak"
    #endif
    #define BSD_ENABLE_ASSERTS
#else
    #define BSD_DEBUG_BREAK()
#endif

#ifdef BSD_ENABLE_ASSERTS
    #define BSD_ASSERT(x, ...)                                                                                         \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                BSD_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                       \
                BSD_DEBUG_BREAK();                                                                                     \
            }                                                                                                          \
        }
    #define BSD_CORE_ASSERT(x, ...)                                                                                    \
        {                                                                                                              \
            if (!(x))                                                                                                  \
            {                                                                                                          \
                BSD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                  \
                BSD_DEBUG_BREAK();                                                                                     \
            }                                                                                                          \
        }
#else
    #define BSD_ASSERT(x, ...)
    #define BSD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BSD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Based
{

    template <typename T> using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args> constexpr Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T> using Ref = std::shared_ptr<T>;

    template <typename T, typename... Args> constexpr Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
} // namespace Based
