#ifndef CLEAN2048_ROUTER_ROUTER_H_
#define CLEAN2048_ROUTER_ROUTER_H_

#include "presenter/Router.h"
#include "use_case/Facade.h"
#include "use_case_interface/BoardPresenter.h"
#include "use_case_interface/GameOverPresenter.h"
#include "use_case_interface/GamePlay.h"
#include "use_case_interface/GameStorage.h"
#include "use_case_interface/ScorePresenter.h"

namespace router {

class Router : public presenter::Router {
 public:
  use_case_interface::GamePlay* getGamePlay() const override {
    return use_case::getGamePlay();
  }

  use_case_interface::GameStorage* getGameStorage() const override {
    return use_case::getGameStorage();
  }

  void setBoardPresenter(
      use_case_interface::BoardPresenter* presenter) const override {
    use_case::setBoardPresenter(presenter);
  }

  void setGameOverPresenter(
      use_case_interface::GameOverPresenter* presenter) const override {
    use_case::setGameOverPresenter(presenter);
  }

  void setScorePresenter(
      use_case_interface::ScorePresenter* presenter) const override {
    use_case::setScorePresenter(presenter);
  }
};

}  // namespace router

#endif
