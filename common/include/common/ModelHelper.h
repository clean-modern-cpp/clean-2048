#ifndef CLEAN2048_COMMON_MODELHELPER_H_
#define CLEAN2048_COMMON_MODELHELPER_H_

#include "common/Model.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const common::Position &position) {
  os << "{" << position.row << ", " << position.col << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const common::MoveAction &moveAction) {
  os << "{" << moveAction.from << ", " << moveAction.to << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os, const common::NewAction &newAction) {
  os << "{" << newAction.pos << ", " << newAction.value << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const common::ChangeAction &changeAction) {
  os << "{" << changeAction.pos << ", " << changeAction.from << ", "
     << changeAction.to << "}";
  return os;
}

template <typename T, typename Hash>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_set<T, Hash> &set) {
  os << "[";
  bool first = true;
  for (const auto &t : set) {
    os << (first ? "" : ", ") << t;
    first = false;
  }
  os << "]\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const common::SwipeAction &action) {
  os << "{\nmoveActions: " << action.moveActions
     << "changeActions: " << action.changeActions << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os, const common::Actions &actions) {
  os << "{\nmoveActions: " << actions.moveActions
     << "newActions: " << actions.newActions
     << "changeActions: " << actions.changeActions << "}";
  return os;
}

}  // namespace std

#endif
