#ifndef CLEAN2048_COMMON_MODELHELPER_H_
#define CLEAN2048_COMMON_MODELHELPER_H_

#include <unordered_set>

#include "common/Model.h"

namespace common {

struct HashPosition {
  std::size_t operator()(const Position &pos) const {
    return std::hash<Index>{}(pos.row) ^ (std::hash<Index>{}(pos.col) < 1);
  }
};

using PositionSet = std::unordered_set<Position, HashPosition>;

inline bool operator==(const Positions &lhs, const Positions &rhs) {
  return PositionSet{lhs.cbegin(), lhs.cend()} ==
         PositionSet{rhs.cbegin(), rhs.cend()};
}

struct HashMoveAction {
  std::size_t operator()(const MoveAction &moveAction) const {
    return HashPosition{}(moveAction.from) ^
           (HashPosition{}(moveAction.to) < 1);
  }
};

using MoveActionSet = std::unordered_set<MoveAction, HashMoveAction>;

struct HashNewAction {
  std::size_t operator()(const NewAction &newAction) const {
    return HashPosition{}(newAction.pos) ^
           (std::hash<Value>{}(newAction.value) < 1);
  }
};

using NewActionSet = std::unordered_set<NewAction, HashNewAction>;

struct HashChangeAction {
  std::size_t operator()(const ChangeAction &changeAction) const {
    return HashPosition{}(changeAction.pos) ^
           (std::hash<Value>{}(changeAction.from) < 1) ^
           (std::hash<Value>{}(changeAction.to) < 2);
  }
};

using ChangeActionSet = std::unordered_set<ChangeAction, HashChangeAction>;

inline bool operator==(const SwipeAction &lhs, const SwipeAction &rhs) {
  return MoveActionSet{lhs.moveActions.cbegin(), lhs.moveActions.cend()} ==
             MoveActionSet{rhs.moveActions.cbegin(), rhs.moveActions.cend()} &&
         ChangeActionSet{lhs.changeActions.cbegin(),
                         lhs.changeActions.cend()} ==
             ChangeActionSet{rhs.changeActions.cbegin(),
                             rhs.changeActions.cend()};
}

inline bool operator==(const Actions &lhs, const Actions &rhs) {
  return MoveActionSet{lhs.moveActions.cbegin(), lhs.moveActions.cend()} ==
             MoveActionSet{rhs.moveActions.cbegin(), rhs.moveActions.cend()} &&
         NewActionSet{lhs.newActions.cbegin(), lhs.newActions.cend()} ==
             NewActionSet{rhs.newActions.cbegin(), rhs.newActions.cend()} &&
         ChangeActionSet{lhs.changeActions.cbegin(),
                         lhs.changeActions.cend()} ==
             ChangeActionSet{rhs.changeActions.cbegin(),
                             rhs.changeActions.cend()};
}

}  // namespace common

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

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &set) {
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
