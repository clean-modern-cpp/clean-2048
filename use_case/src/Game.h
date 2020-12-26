#ifndef CLEAN2048_USECASE_GAME_H_
#define CLEAN2048_USECASE_GAME_H_

#include "entity/Board.h"
#include "use_case/GamePlay.h"

namespace use_case {

class Game : public GamePlay {
 public:
  void newGame() override {}
  void swipe(Direction) override {}

 private:
  entity::Board board;
};

}  // namespace use_case

#endif
