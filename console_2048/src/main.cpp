#include "console_ui/Application.h"
#include "router/Router.h"
#include "storage/Storage.h"

int main() {
  presenter::setRouter(std::make_unique<router::Router>());
  use_case::setStorage(std::make_unique<storage::Storage>());

  console_ui::Application app;
  app.execute();

  return 0;
}
