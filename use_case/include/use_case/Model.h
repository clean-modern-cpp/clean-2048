#ifndef CLEAN2048_USECASE_MODEL_H_
#define CLEAN2048_USECASE_MODEL_H_

#include "common/Model.h"

namespace use_case {

using Index = common::model::Index;
using Value = common::model::Value;
using Direction = common::model::Direction;
using Position = common::model::Position;
using Positions = common::model::Positions;
using MoveAction = common::model::MoveAction;
using NewAction = common::model::NewAction;
using ChangeAction = common::model::ChangeAction;

struct Actions {
  std::vector<MoveAction> moveActions;
  std::vector<NewAction> newActions;
  std::vector<ChangeAction> changeActions;
};

}  // namespace use_case

#endif
