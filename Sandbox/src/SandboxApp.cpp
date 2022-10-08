#include "Based.h"

class Sandbox : public Based::Application {
public:
  Sandbox() {}

  ~Sandbox() {}
};

Based::Application *Based::CreateApplication() { return new Sandbox(); }
