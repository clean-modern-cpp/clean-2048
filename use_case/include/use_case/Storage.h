#ifndef CLEAN2048_USECASE_STORAGE_H_
#define CLEAN2048_USECASE_STORAGE_H_

#include <memory>

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case {

struct ScoreData {
  int score;
  int bestScore;
};

inline bool operator==(const ScoreData& lhs, const ScoreData& rhs) {
  return lhs.score == rhs.score && lhs.bestScore == rhs.bestScore;
}

struct BoardData {
  common::Index rows;
  common::Index cols;
  common::NewActions newActions;
};

inline bool operator==(const BoardData& lhs, const BoardData& rhs) {
  return lhs.rows == rhs.rows && lhs.cols && lhs.cols == rhs.cols &&
         lhs.newActions == rhs.newActions;
}

class Storage : public common::NonCopyable {
 public:
  virtual ScoreData loadScore() = 0;
  virtual BoardData loadBoard() = 0;

  virtual void saveScore(const ScoreData& scoreData) = 0;
  virtual void saveBoard(const BoardData& boardData) = 0;

  virtual void clear() = 0;
};

void setStorage(const std::unique_ptr<Storage> storage);

}  // namespace use_case

#endif
