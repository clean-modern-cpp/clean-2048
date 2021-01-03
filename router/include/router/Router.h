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
  use_case_interface::GamePlay* getGamePlay() override {
    return use_case::getGamePlay();
  }

  use_case_interface::GameStorage* getGameStorage() override {
    return use_case::getGameStorage();
  }

  void setBoardPresenter(
      use_case_interface::BoardPresenter* presenter) override {
    use_case::setBoardPresenter(presenter);
  }

  void setScorePresenter(
      use_case_interface::ScorePresenter* presenter) override {
    use_case::setScorePresenter(presenter);
  }

  void setGameOverPresenter(
      use_case_interface::GameOverPresenter* presenter) override {
    use_case::setGameOverPresenter(presenter);
  }
};

}  // namespace router

#endif
