#include "presenter/Controller.h"

#include "use_case/GamePlayUseCase.h"

namespace presenter {

class Controller::Impl {
 public:
  Impl() : gamePlayUseCase{use_case::getGamePlayUseCase()} {}

  void newGame() { gamePlayUseCase->newGame(); }
  void swipe(common::Direction d) { gamePlayUseCase->swipe(d); }

 private:
  use_case::GamePlayUseCase* gamePlayUseCase;
};

Controller::Controller() : impl(std::make_unique<Impl>()) {}

Controller::~Controller() {}

void Controller::newGame() { impl->newGame(); }

void Controller::swipe(common::Direction d) { impl->swipe(d); }

}  // namespace presenter
