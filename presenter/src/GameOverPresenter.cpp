#include "presenter/GameOverPresenter.h"

#include "GetRouter.h"
#include "use_case_interface/GameOverPresenter.h"

namespace presenter {

class GameOverPresenter::Impl : public use_case_interface::GameOverPresenter {
 public:
  void setDelegate(GameOverPresenterDelegate* d) {
    delegate = d;
    getRouter()->setGameOverPresenter(this);
  }

  void present() override {
    if (delegate) {
      delegate->present();
    }
  }

 private:
  GameOverPresenterDelegate* delegate = nullptr;
};

GameOverPresenter::GameOverPresenter() : impl{std::make_unique<Impl>()} {}

GameOverPresenter::~GameOverPresenter() {}

void GameOverPresenter::setDelegate(GameOverPresenterDelegate* d) {
  impl->setDelegate(d);
}

}  // namespace presenter
