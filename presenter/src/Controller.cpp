#include "presenter/Controller.h"

#include "GetRouter.h"
#include "use_case_interface/GamePlay.h"
#include "use_case_interface/GameStorage.h"

namespace presenter {

class Controller::Impl {
 public:
  Impl()
      : gamePlay{getRouter()->getGamePlay()},
        gameStorage{getRouter()->getGameStorage()} {}

  void newGame() { gameStorage->newGame(); }

  void loadGame() { gameStorage->loadGame(); }

  void saveGame() { gameStorage->saveGame(); }

  void swipe(common::Direction dir) { gamePlay->swipe(dir); }

 private:
  use_case_interface::GamePlay* gamePlay;
  use_case_interface::GameStorage* gameStorage;
};

Controller::Controller() : impl(std::make_unique<Impl>()) {}

Controller::~Controller() {}

void Controller::newGame() { impl->newGame(); }

void Controller::loadGame() { impl->loadGame(); }

void Controller::saveGame() { impl->saveGame(); }

void Controller::swipe(common::Direction dir) { impl->swipe(dir); }

}  // namespace presenter
