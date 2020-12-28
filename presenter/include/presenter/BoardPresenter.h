#ifndef CLEAN2048_PRESENTER_BOARDPRESENTER_H_
#define CLEAN2048_PRESENTER_BOARDPRESENTER_H_

#include <memory>

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace presenter {

class BoardPresenterDelegate : public common::NonCopyable {
 public:
  virtual void intiWithDimension(int rows, int columns) = 0;
  virtual void present(common::Actions actions) = 0;
};

class BoardPresenter {
 public:
  BoardPresenter();
  ~BoardPresenter();

  void setDelegate(BoardPresenterDelegate* d);

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace presenter

#endif
