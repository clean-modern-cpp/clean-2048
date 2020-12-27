#include "Game.h"

#include "entity/Board.h"

namespace use_case {

Game<entity::Board> game;

GamePlay* getGamePlay() { return &game; }

}  // namespace use_case
