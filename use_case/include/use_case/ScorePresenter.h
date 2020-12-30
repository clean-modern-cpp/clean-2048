#ifndef CLEAN2048_USECASE_SCOREPRESENTER_H_
#define CLEAN2048_USECASE_SCOREPRESENTER_H_

#include "common/NonCopyable.h"

namespace use_case {

class ScorePresenter : public common::NonCopyable {
 public:
  virtual void present(int score, int bestScore) = 0;
};

void setScorePresenter(ScorePresenter* presenter);

}  // namespace use_case

#endif
