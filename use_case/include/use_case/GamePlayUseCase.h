#ifndef CLEAN2048_USECASE_GAMEPLAY_H_
#define CLEAN2048_USECASE_GAMEPLAY_H_

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case {

class GamePlayUseCase : public common::NonCopyable {
 public:
  virtual void newGame() = 0;
  virtual void startGame() = 0;
  virtual void swipe(common::Direction direction) = 0;
};

GamePlayUseCase* getGamePlayUseCase();

}  // namespace use_case

#endif
