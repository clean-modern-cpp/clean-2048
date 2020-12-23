#include "console_ui/Application.h"

#include <unordered_map>

#include "BoardView.h"
#include "ControlView.h"
#include "ScoreView.h"
#include "common/Model.h"
#include "presenter/Controller.h"

namespace console_ui {

class Application::Impl {
 public:
  Impl() {}

  void execute() {
    // controller.newGame();
    while (true) {
      show();
      const auto input = controlView.getInput();
      if (input == "q") {
        break;
      } else if (!input.empty() &&
                 directionMap.find(input[0]) != directionMap.end()) {
        // controller.move(directionMap.at(input[0]));
      }
    }
  }

 private:
  void show() {
    scoreView.show();
    std::cout << boardView.body();
    controlView.show();
    std::cout << std::endl;
  }

  ScoreView scoreView;
  BoardView boardView;
  ControlView controlView;

  // presenter::Controller controller;
  presenter::BoardPresenter boardPresenter;

  inline static const std::unordered_map<char, common::model::Direction>
      directionMap{
          {'l', common::model::Direction::left},
          {'r', common::model::Direction::right},
          {'u', common::model::Direction::up},
          {'d', common::model::Direction::down},
      };
};

Application::Application() : impl(std::make_unique<Impl>()) {}

Application::~Application() {}

void Application::execute() { impl->execute(); }

}  // namespace console_ui
