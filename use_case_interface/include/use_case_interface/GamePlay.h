#ifndef CLEAN2048_USECASE_GAMEPLAY_H_
#define CLEAN2048_USECASE_GAMEPLAY_H_

#include "common/Model.h"
#include "common/NonCopyable.h"

namespace use_case_interface {

class GamePlay : public common::NonCopyable {
 public:
  virtual void swipe(common::Direction direction) = 0;
};

}  // namespace use_case_interface

#endif
