#ifndef CLEAN2048_USECASE_GAMESTORAGE_H_
#define CLEAN2048_USECASE_GAMESTORAGE_H_

#include "common/NonCopyable.h"

namespace use_case {

class GameStorageUseCase : public common::NonCopyable {
 public:
  virtual void saveGame() = 0;
};

GameStorageUseCase* getGameStorageUseCase();

}  // namespace use_case

#endif
