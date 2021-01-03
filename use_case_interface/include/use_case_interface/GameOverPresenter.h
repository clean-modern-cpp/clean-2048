#ifndef CLEAN2048_USECASE_GAMEOVERPRESENTER_H_
#define CLEAN2048_USECASE_GAMEOVERPRESENTER_H_

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case_interface {

class GameOverPresenter : public common::NonCopyable {
 public:
  virtual void present() = 0;
};

}  // namespace use_case_interface

#endif
