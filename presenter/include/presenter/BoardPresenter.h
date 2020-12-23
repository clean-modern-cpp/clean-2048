#ifndef CLEAN2048_PRESENTER_BOARDPRESENTER_H_
#define CLEAN2048_PRESENTER_BOARDPRESENTER_H_

#include <vector>

#include "common/Model.h"
#include "use_case/BoardPresenter.h"

namespace presenter {

class BoardPresenterDelegate {
 public:
  BoardPresenterDelegate() = default;
  BoardPresenterDelegate(const BoardPresenterDelegate&) = delete;
  BoardPresenterDelegate& operator=(const BoardPresenterDelegate&) = delete;
  virtual ~BoardPresenterDelegate() = default;

  virtual void intiWithDimension(int rows, int columns) = 0;
  virtual void presentActions(common::model::Actions actions) = 0;
};

class BoardPresenter : public use_case::BoardPresenter {
 public:
  void setDelegate(BoardPresenterDelegate* d) {
    delegate = d;
    // use_case::Facade::setBoardPresenter(this);
  }

  void initWithDimension(int row, int column) override {
    delegate->intiWithDimension(row, column);
  }

  void presentActions(common::model::Actions actions) override {
    delegate->presentActions(actions);
  }

 private:
  BoardPresenterDelegate* delegate;
};

}  // namespace presenter

#endif
