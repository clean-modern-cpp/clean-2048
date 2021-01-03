#ifndef CLEAN2048_USECASEINTERFACE_STORAGE_H_
#define CLEAN2048_USECASEINTERFACE_STORAGE_H_

#include <memory>

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case_interface {

struct GameData {
  int bestScore = 0;
  int score = 0;
  bool isGameOver = true;
  common::Index rows;
  common::Index cols;
  common::NewActions newActions;
};

inline bool operator==(const GameData& lhs, const GameData& rhs) {
  return lhs.bestScore == rhs.bestScore && lhs.score == rhs.score &&
         lhs.isGameOver == rhs.isGameOver && lhs.rows == rhs.rows &&
         lhs.cols == rhs.cols && lhs.newActions == rhs.newActions;
}

class Storage : public common::NonCopyable {
 public:
  virtual GameData loadGame() = 0;

  virtual void saveGame(const GameData& gameData) = 0;

  virtual void clear() = 0;
};

}  // namespace use_case_interface

#endif
