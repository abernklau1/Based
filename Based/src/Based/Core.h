#pragma once

#define BASED_API

#ifdef BSD_DEBUG
// #define BSD_ENABLE_ASSERTS
#endif

#ifdef BSD_ENABLE_ASSERTS
#define BSD_ASSERT(x, ...)                                                     \
  {                                                                            \
    if (!(x)) {                                                                \
      BSD_ERROR("Assertion Failed: {0}", __VA_ARGS__);                         \
    // __debugbreak();                                                          \
    }                                                                          \
  }
#define BSD_CORE_ASSERT(x, ...)                                                \
  {                                                                            \
    if (!(x)) {                                                                \
      BSD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                    \
    // __debugbreak();                                                          \
    }                                                                          \
  }
#else
#define BSD_ASSERT(x, ...)
#define BSD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BSD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
