#ifndef CLEAN2048_CONSOLEUI_SCOREVIEW_H_
#define CLEAN2048_CONSOLEUI_SCOREVIEW_H_

#include <iostream>

namespace console_ui {

class ScoreView {
 public:
  void show() { std::cout << "Score View\n\n"; }
};

}  // namespace console_ui

#endif
