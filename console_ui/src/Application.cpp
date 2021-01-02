#include "console_ui/Application.h"

#include <iostream>
#include <unordered_map>

#include "BoardView.h"
#include "ScoreView.h"
#include "presenter/BoardPresenter.h"
#include "presenter/Controller.h"
#include "presenter/GameOverPresenter.h"
#include "presenter/ScorePresenter.h"

namespace console_ui {

class Application::Impl : public presenter::GameOverPresenterDelegate {
 public:
  Impl() {
    boardPresenter.setDelegate(&boardView);
    scorePresenter.setDelegate(&scoreView);
    gameOverPresenter.setDelegate(this);
  }

  void execute() {
    controller.loadGame();
    while (true) {
      show();
      const auto input = getInput();
      if (isGameOver || input == "n") {
        isGameOver = false;
        controller.newGame();
      } else if (input == "q") {
        controller.saveGame();
        break;
      } else if (!input.empty() &&
                 directionMap.find(input[0]) != directionMap.end()) {
        controller.swipe(directionMap.at(input[0]));
      }
    }
  }

  void present() override { isGameOver = true; }

 private:
  void show() {
    std::cout << scoreView.body();
    std::cout << boardView.body();

    if (isGameOver) {
      std::cout << "Game Over!\n";
      std::cout << "Press any key to continue:\n";
    } else {
      std::cout << "Please input:\n";
      std::cout << "  - l: Left, r: Right, u: up, d: Down\n";
      std::cout << "  - n: New game, q: Quit\n";
      std::cout << std::endl;
    }
  }

  std::string getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
  }

  bool isGameOver = false;

  ScoreView scoreView;
  BoardView boardView;

  presenter::Controller controller;
  presenter::BoardPresenter boardPresenter;
  presenter::ScorePresenter scorePresenter;
  presenter::GameOverPresenter gameOverPresenter;

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
