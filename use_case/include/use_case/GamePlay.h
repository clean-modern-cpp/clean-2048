#ifndef CLEAN2048_USECASE_GAMEPLAY_H_
#define CLEAN2048_USECASE_GAMEPLAY_H_

#include "common/Model.h"
#include "common/NonCopyable.h"
#include "use_case/Model.h"

namespace use_case {

using Direction = common::model::Direction;

class GamePlay : public common::NonCopyable {
 public:
  virtual Actions newGame() = 0;
  virtual void swipe(Direction direction) = 0;
};

GamePlay* getGamePlay();

}  // namespace use_case

#endif
