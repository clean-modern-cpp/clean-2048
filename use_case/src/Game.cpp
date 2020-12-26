#include "Game.h"

namespace use_case {

Game game;

GamePlay* getGamePlay() { return &game; }

}  // namespace use_case
