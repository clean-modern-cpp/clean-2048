#include "presenter/ScorePresenter.h"

#include "use_case/ScorePresenter.h"

namespace presenter {

class ScorePresenter::Impl : public use_case::ScorePresenter {
 public:
  void setDelegate(ScorePresenterDelegate* d) {
    delegate = d;
    use_case::setScorePresenter(this);
  }

  void present(int score, int bestScore) override {
    if (delegate) {
      delegate->present(score, bestScore);
    }
  }

 private:
  ScorePresenterDelegate* delegate = nullptr;
};

ScorePresenter::ScorePresenter() : impl{std::make_unique<Impl>()} {}

ScorePresenter::~ScorePresenter() {}

void ScorePresenter::setDelegate(ScorePresenterDelegate* d) {
  impl->setDelegate(d);
}

}  // namespace presenter
