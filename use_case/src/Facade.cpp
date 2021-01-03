#include "use_case/Facade.h"

#include "Game.h"
#include "entity/Board.h"
#include "entity/Score.h"

namespace use_case {

namespace global {

Game<entity::Board, entity::Score> game;

}

use_case_interface::GamePlay* getGamePlay() { return &global::game; }

use_case_interface::GameStorage* getGameStorage() { return &global::game; }

void setBoardPresenter(use_case_interface::BoardPresenter* presenter) {
  global::game.setBoardPresenter(presenter);
}

void setScorePresenter(use_case_interface::ScorePresenter* presenter) {
  global::game.setScorePresenter(presenter);
}

void setGameOverPresenter(use_case_interface::GameOverPresenter* presenter) {
  global::game.setGameOverPresenter(presenter);
}

void setRandom(std::unique_ptr<use_case_interface::Random> random) {
  global::game.setRandom(std::move(random));
}

void setStorage(std::unique_ptr<use_case_interface::Storage> storage) {
  global::game.setStorage(std::move(storage));
}

}  // namespace use_case
