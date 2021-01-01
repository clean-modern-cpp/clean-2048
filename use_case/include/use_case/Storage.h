#ifndef CLEAN2048_USECASE_STORAGE_H_
#define CLEAN2048_USECASE_STORAGE_H_

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case {

struct ScoreStorage {
  int score;
  int bestScore;
};

inline bool operator==(const ScoreStorage& lhs, const ScoreStorage& rhs) {
  return lhs.score == rhs.score && lhs.bestScore == rhs.bestScore;
}

struct BoardStorage {
  common::Index rows;
  common::Index cols;
  common::Values values;
};

inline bool operator==(const BoardStorage& lhs, const BoardStorage& rhs) {
  return lhs.rows == rhs.rows && lhs.cols && lhs.cols == rhs.cols &&
         lhs.values == rhs.values;
}

class Storage : public common::NonCopyable {
 public:
  virtual ScoreStorage loadScore() = 0;
  virtual BoardStorage loadBoard() = 0;

  virtual void saveScore(const ScoreStorage& scoreStorage) = 0;
  virtual void saveBoard(const BoardStorage& boardStorage) = 0;
};

}  // namespace use_case

#endif
