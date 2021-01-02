#include "console_ui/Application.h"
#include "storage/Storage.h"
#include "use_case/Storage.h"

int main() {
  console_ui::Application app;
  use_case::setStorage(std::make_unique<storage::Storage>());
  app.execute();

  return 0;
}
