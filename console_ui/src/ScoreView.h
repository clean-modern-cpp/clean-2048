#ifndef CLEAN2048_CONSOLEUI_SCOREVIEW_H_
#define CLEAN2048_CONSOLEUI_SCOREVIEW_H_

#include <string>

#include "presenter/ScorePresenter.h"

namespace console_ui {

class ScoreView : public presenter::ScorePresenterDelegate {
 public:
  std::string body() {
    return "[ 2048 ] [ Score: " + std::to_string(score) + "] " +
           "[Best Score: " + std::to_string(bestScore) + "]\n";
  }

  void present(int s, int bs) override {
    score = s;
    bestScore = bs;
  }

 private:
  int score = 0;
  int bestScore = 0;
};

}  // namespace console_ui

#endif
