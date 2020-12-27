#ifndef CLEAN2048_PRESENTER_BOARDPRESENTER_H_
#define CLEAN2048_PRESENTER_BOARDPRESENTER_H_

#include <vector>

#include "use_case/BoardPresenter.h"
#include "use_case/Model.h"

namespace presenter {

class BoardPresenterDelegate {
 public:
  BoardPresenterDelegate() = default;
  BoardPresenterDelegate(const BoardPresenterDelegate&) = delete;
  BoardPresenterDelegate& operator=(const BoardPresenterDelegate&) = delete;
  virtual ~BoardPresenterDelegate() = default;

  virtual void intiWithDimension(int rows, int columns) = 0;
  virtual void present(use_case::Actions actions) = 0;
};

class BoardPresenter : public use_case::BoardPresenter {
 public:
  void setDelegate(BoardPresenterDelegate* d);

  void initWithDimension(int row, int column) const override;

  void present(use_case::Actions actions) const override;

 private:
  BoardPresenterDelegate* delegate = nullptr;
};

}  // namespace presenter

#endif
