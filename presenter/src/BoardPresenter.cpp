#include "presenter/BoardPresenter.h"

#include <cassert>

#include "GetRouter.h"
#include "use_case_interface/BoardPresenter.h"

namespace presenter {

class BoardPresenter::Impl : public use_case_interface::BoardPresenter {
 public:
  void setDelegate(BoardPresenterDelegate* d) {
    delegate = d;
    getRouter()->setBoardPresenter(this);
  }

  void initWithDimension(int row, int column) override {
    assert(delegate && "Delegate is null");
    delegate->initWithDimension(row, column);
  }
  void present(common::Actions actions) override {
    assert(delegate && "Delegate is null");
    delegate->present(actions);
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
