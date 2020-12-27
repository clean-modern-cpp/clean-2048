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
  virtual void present(common::Actions actions) = 0;
};

class BoardPresenter : public use_case::BoardPresenter {
 public:
  void setDelegate(BoardPresenterDelegate* d);

  void initWithDimension(int row, int column) const override;

  void present(common::Actions actions) const override;

 private:
  BoardPresenterDelegate* delegate = nullptr;
};

}  // namespace presenter

#endif
