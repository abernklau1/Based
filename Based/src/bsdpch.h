#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef BSD_PLATFORM_MAC
#include <TargetConditionals.h>
#elif BSD_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#pragma hdrstop