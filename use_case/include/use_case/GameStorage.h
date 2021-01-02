#ifndef CLEAN2048_USECASE_GAMESTORAGE_H_
#define CLEAN2048_USECASE_GAMESTORAGE_H_

#include "common/NonCopyable.h"

namespace use_case {

class GameStorage : public common::NonCopyable {
 public:
  virtual void newGame() = 0;
  virtual void loadGame() = 0;
  virtual void saveGame() = 0;
};

GameStorage* getGameStorage();

}  // namespace use_case

#endif
