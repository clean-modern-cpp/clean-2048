#include "presenter/GameOverPresenter.h"

#include "use_case/GameOverPresenter.h"

namespace presenter {

class GameOverPresenter::Impl : public use_case::GameOverPresenter {
 public:
  void setDelegate(GameOverPresenterDelegate* d) {
    delegate = d;
    use_case::setGameOverPresenter(this);
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
