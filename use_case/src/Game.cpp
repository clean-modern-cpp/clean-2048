#include "Game.h"

#include "entity/Board.h"
#include "use_case/BoardPresenter.h"

namespace use_case {

Game<entity::Board> game;

GamePlay* getGamePlay() { return &game; }

void setBoardPresenter(BoardPresenter* presenter) {
  game.setBoardPresenter(presenter);
}

}  // namespace use_case
