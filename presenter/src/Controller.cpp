#include "presenter/Controller.h"

#include "use_case/GamePlay.h"

namespace presenter {

class Controller::Impl {
 public:
  Impl() : gamePlay{use_case::getGamePlay()} {}

  void newGame() { gamePlay->newGame(); }

 private:
  use_case::GamePlay* gamePlay;
};

Controller::Controller() : impl(std::make_unique<Impl>()) {}

Controller::~Controller() {}

void Controller::newGame() { impl->newGame(); }

}  // namespace presenter
