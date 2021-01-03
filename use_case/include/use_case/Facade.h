#ifndef CLEAN2048_USECASE_FACADE_H_
#define CLEAN2048_USECASE_FACADE_H_

#include <memory>

#include "use_case_interface/BoardPresenter.h"
#include "use_case_interface/GameOverPresenter.h"
#include "use_case_interface/GamePlay.h"
#include "use_case_interface/GameStorage.h"
#include "use_case_interface/ScorePresenter.h"

namespace use_case {

use_case_interface::GamePlay* getGamePlay();
use_case_interface::GameStorage* getGameStorage();

void setBoardPresenter(use_case_interface::BoardPresenter* presenter);
void setGameOverPresenter(use_case_interface::GameOverPresenter* presenter);
void setScorePresenter(use_case_interface::ScorePresenter* presenter);

}  // namespace use_case

#endif
