#include "Game.h"

#include "entity/Board.h"
#include "entity/Score.h"
#include "use_case/BoardPresenter.h"

namespace use_case {

Game<entity::Board, entity::Score> game;

GamePlay* getGamePlay() { return &game; }

void setBoardPresenter(BoardPresenter* presenter) {
  game.setBoardPresenter(presenter);
}

void setScorePresenter(ScorePresenter* presenter) {
  game.setScorePresenter(presenter);
}

}  // namespace use_case
