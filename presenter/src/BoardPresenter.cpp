#include "presenter/BoardPresenter.h"

#include "use_case/BoardPresenter.h"

namespace presenter {

class BoardPresenter::Impl : public use_case::BoardPresenter {
 public:
  void setDelegate(BoardPresenterDelegate* d) {
    delegate = d;
    use_case::setBoardPresenter(this);
  }

  void initWithDimension(int row, int column) override {
    if (delegate) {
      delegate->initWithDimension(row, column);
    }
  }
  void present(common::Actions actions) override {
    if (delegate) {
      delegate->present(actions);
    }
  }

 private:
  BoardPresenterDelegate* delegate = nullptr;
};

BoardPresenter::BoardPresenter() : impl{std::make_unique<Impl>()} {}

BoardPresenter::~BoardPresenter() {}

void BoardPresenter::setDelegate(BoardPresenterDelegate* d) {
  impl->setDelegate(d);
}

}  // namespace presenter
