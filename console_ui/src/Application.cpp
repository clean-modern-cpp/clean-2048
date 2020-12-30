#include "console_ui/Application.h"

#include <iostream>
#include <unordered_map>

#include "BoardView.h"
#include "ScoreView.h"
#include "presenter/BoardPresenter.h"
#include "presenter/Controller.h"
#include "presenter/ScorePresenter.h"

namespace console_ui {

class Application::Impl {
 public:
  Impl() {
    boardPresenter.setDelegate(&boardView);
    scorePresenter.setDelegate(&scoreView);
  }

  void execute() {
    controller.newGame();
    while (true) {
      show();
      const auto input = getInput();
      if (input == "q") {
        break;
      } else if (!input.empty() &&
                 directionMap.find(input[0]) != directionMap.end()) {
        controller.swipe(directionMap.at(input[0]));
      }
    }
  }

 private:
  void show() {
    std::cout << scoreView.body();
    std::cout << boardView.body();

    std::cout << "Please input:\n";
    std::cout << "  - l: Left, r: Right, u: up, d: Down\n";
    std::cout << "  - q: Quit\n";
    std::cout << std::endl;
  }

  std::string getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
  }

  ScoreView scoreView;
  BoardView boardView;

  presenter::Controller controller;
  presenter::BoardPresenter boardPresenter;
  presenter::ScorePresenter scorePresenter;

  inline static const std::unordered_map<char, common::Direction> directionMap{
      {'l', common::Direction::left},
      {'r', common::Direction::right},
      {'u', common::Direction::up},
      {'d', common::Direction::down},
  };
};

Application::Application() : impl(std::make_unique<Impl>()) {}

Application::~Application() {}

void Application::execute() { impl->execute(); }

}  // namespace console_ui
