#ifndef CLEAN2048_USECASEINTERFACE_GAMESTORAGE_H_
#define CLEAN2048_USECASEINTERFACE_GAMESTORAGE_H_

#include "common/NonCopyable.h"

namespace use_case_interface {

class GameStorage : public common::NonCopyable {
 public:
  virtual void newGame() = 0;
  virtual void loadGame() = 0;
  virtual void saveGame() = 0;
};

}  // namespace use_case_interface

#endif
