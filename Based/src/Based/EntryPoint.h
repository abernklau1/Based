#pragma once

extern Based::Application *Based::CreateApplication();

int main(int argc, char **argv) {
  auto app = Based::CreateApplication();
  app->Run();
  delete app;
}
