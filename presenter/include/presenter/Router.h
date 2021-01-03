#ifndef CLEAN2048_PRESENTER_ROUTER_H_
#define CLEAN2048_PRESENTER_ROUTER_H_

#include <memory>

#include "common/NonCopyable.h"
#include "use_case_interface/BoardPresenter.h"
#include "use_case_interface/GameOverPresenter.h"
#include "use_case_interface/GamePlay.h"
#include "use_case_interface/GameStorage.h"
#include "use_case_interface/ScorePresenter.h"

namespace presenter {

class Router : public common::NonCopyable {
 public:
  virtual use_case_interface::GamePlay* getGamePlay() const = 0;
  virtual use_case_interface::GameStorage* getGameStorage() const = 0;

  virtual void setBoardPresenter(
      use_case_interface::BoardPresenter* presenter) const = 0;
  virtual void setGameOverPresenter(
      use_case_interface::GameOverPresenter* presenter) const = 0;
  virtual void setScorePresenter(
      use_case_interface::ScorePresenter* presenter) const = 0;
};

void setRouter(std::unique_ptr<Router> router);

}  // namespace presenter

#endif
