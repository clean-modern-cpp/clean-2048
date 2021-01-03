#ifndef CLEAN2048_USECASEINTERFACE_SCOREPRESENTER_H_
#define CLEAN2048_USECASEINTERFACE_SCOREPRESENTER_H_

#include "common/NonCopyable.h"

namespace use_case_interface {

class ScorePresenter : public common::NonCopyable {
 public:
  virtual void present(int score, int bestScore) = 0;
};

}  // namespace use_case_interface

#endif
