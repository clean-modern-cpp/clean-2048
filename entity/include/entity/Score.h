#ifndef CLEAN2048_ENTITY_SCORE_H_
#define CLEAN2048_ENTITY_SCORE_H_

#include <memory>

#include "common/Model.h"

namespace entity {

class Score {
 public:
  Score();
  ~Score();

  int getScore() const;
  int getBestScore() const;

  void update(const common::SwipeAction& action);

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace entity

#endif
