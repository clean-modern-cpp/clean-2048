#include "presenter/BoardPresenter.h"

namespace presenter {

void BoardPresenter::setDelegate(BoardPresenterDelegate* d) {
  delegate = d;
  use_case::setBoardPresenter(this);
}

void BoardPresenter::initWithDimension(int row, int column) const {
  if (delegate) {
    delegate->intiWithDimension(row, column);
  }
}

void BoardPresenter::present(use_case::Actions actions) const {
  if (delegate) {
    delegate->present(actions);
  }
}

}  // namespace presenter
