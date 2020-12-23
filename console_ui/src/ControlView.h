#ifndef CLEAN2048_CONSOLEUI_CONTROLVIEW_H_
#define CLEAN2048_CONSOLEUI_CONTROLVIEW_H_

#include <iostream>
#include <string>

namespace console_ui {

class ControlView {
 public:
  void show() {
    std::cout << "Please input:\n";
    std::cout << "  - l: Left, r: Right, u: up, d: Down\n";
    std::cout << "  - q: Quit\n";
  }

  std::string getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
  }
};

}  // namespace console_ui

#endif
