#ifndef CLEAN2048_ENTITY_SCORE_H_
#define CLEAN2048_ENTITY_SCORE_H_

#include <memory>

#include "common/Model.h"

namespace entity {

class Score {
 public:
  Score();
  Score(int score, int bestScore);
  ~Score();

  Score(Score&&);
  Score& operator=(Score&&);

  int getScore() const;
  int getBestScore() const;

  void update(const common::SwipeAction& action);
  void reset();

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace entity

#endif
