#ifndef CLEAN2048_CONSOLEUI_APPLICATION_H_
#define CLEAN2048_CONSOLEUI_APPLICATION_H_

#include <memory>

namespace console_ui {

class Application {
 public:
  Application();
  ~Application();

  void execute();

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace console_ui

#endif
