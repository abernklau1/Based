#pragma once
#include "Core.h"

namespace Based {
class BASED_API Application {
public:
  Application();
  virtual ~Application();

  void Run();
};

// To be defined in client

Application *CreateApplication();
} // namespace Based
