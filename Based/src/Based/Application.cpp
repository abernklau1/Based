#include "Application.h"
#include <stdio.h>

namespace Based {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  while (true) {
    printf("Hello");
  }
}
} // namespace Based
