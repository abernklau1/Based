#include "Application.h"

#include "Based/Events/ApplicationEvent.h"
#include "Based/Log.h"

namespace Based {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
  WindowResizeEvent e(1200, 720);
  BSD_TRACE(e);

  while (true)
    ;
}
} // namespace Based
