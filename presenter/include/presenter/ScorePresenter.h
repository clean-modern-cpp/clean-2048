#ifndef CLEAN2048_PRESENTER_SCOREPRESENTER_H_
#define CLEAN2048_PRESENTER_SCOREPRESENTER_H_

#include <memory>

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace presenter {

class ScorePresenterDelegate : public common::NonCopyable {
 public:
  virtual void present(int score, int bestScore) = 0;
};

class ScorePresenter {
 public:
  ScorePresenter();
  ~ScorePresenter();

  void setDelegate(ScorePresenterDelegate* d);

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace presenter

#endif
