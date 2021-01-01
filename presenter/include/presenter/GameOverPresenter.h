#ifndef CLEAN2048_PRESENTER_GAMEOVERPRESENTER_H_
#define CLEAN2048_PRESENTER_GAMEOVERPRESENTER_H_

#include <memory>

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace presenter {

class GameOverPresenterDelegate : public common::NonCopyable {
 public:
  virtual void present() = 0;
};

class GameOverPresenter {
 public:
  GameOverPresenter();
  ~GameOverPresenter();

  void setDelegate(GameOverPresenterDelegate* d);

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace presenter

#endif
