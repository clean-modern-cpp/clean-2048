#include "Game.h"

#include "entity/Board.h"
#include "entity/Score.h"

namespace use_case {

Game<entity::Board, entity::Score> game;

GamePlay* getGamePlay() { return &game; }

GameStorage* getGameStorage() { return &game; }

void setBoardPresenter(BoardPresenter* presenter) {
  game.setBoardPresenter(presenter);
}

void setScorePresenter(ScorePresenter* presenter) {
  game.setScorePresenter(presenter);
}

void setGameOverPresenter(GameOverPresenter* presenter) {
  game.setGameOverPresenter(presenter);
}

void setRandom(std::unique_ptr<Random> random) {
  game.setRandom(std::move(random));
}

void setStorage(std::unique_ptr<Storage> storage) {
  game.setStorage(std::move(storage));
}

}  // namespace use_case
