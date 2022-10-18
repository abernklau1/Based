#pragma once

#include "Based.h"

extern Based::Application *Based::CreateApplication();

int main(int argc, char **argv) {
  Based::Log::Init();

  BSD_CORE_INFO("Initialized Core log");
  BSD_INFO("Initialized log");
  auto app = Based::CreateApplication();
  app->Run();
  delete app;
}
