#ifndef CLEAN2048_COMMON_MODELHELPER_H_
#define CLEAN2048_COMMON_MODELHELPER_H_

#include <ostream>
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
  std::size_t operator()(const MoveAction &action) const {
    return HashPosition{}(action.from) ^ (HashPosition{}(action.to) < 1);
  }
};

using MoveActionSet = std::unordered_set<MoveAction, HashMoveAction>;

struct HashMergeAction {
  std::size_t operator()(const MergeAction &action) const {
    return HashPosition{}(action.pos) ^
           (std::hash<Value>{}(action.toValue) < 1);
  }
};

using MergeActionSet = std::unordered_set<MergeAction, HashMergeAction>;

struct HashNewAction {
  std::size_t operator()(const NewAction &action) const {
    return HashPosition{}(action.pos) ^ (std::hash<Value>{}(action.value) < 1);
  }
};

using NewActionSet = std::unordered_set<NewAction, HashNewAction>;

inline bool operator==(const SwipeAction &lhs, const SwipeAction &rhs) {
  return MoveActionSet{lhs.moveActions.cbegin(), lhs.moveActions.cend()} ==
             MoveActionSet{rhs.moveActions.cbegin(), rhs.moveActions.cend()} &&
         MergeActionSet{lhs.mergeActions.cbegin(), lhs.mergeActions.cend()} ==
             MergeActionSet{rhs.mergeActions.cbegin(), rhs.mergeActions.cend()};
}

inline bool operator==(const Actions &lhs, const Actions &rhs) {
  return MoveActionSet{lhs.moveActions.cbegin(), lhs.moveActions.cend()} ==
             MoveActionSet{rhs.moveActions.cbegin(), rhs.moveActions.cend()} &&
         MergeActionSet{lhs.mergeActions.cbegin(), lhs.mergeActions.cend()} ==
             MergeActionSet{rhs.mergeActions.cbegin(),
                            rhs.mergeActions.cend()} &&
         NewActionSet{lhs.newActions.cbegin(), lhs.newActions.cend()} ==
             NewActionSet{rhs.newActions.cbegin(), rhs.newActions.cend()};
}

}  // namespace common

namespace std {

inline std::ostream &operator<<(std::ostream &os,
                                const common::Position &position) {
  os << "{" << position.row << ", " << position.col << "}";
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const common::MoveAction &action) {
  os << "{" << action.from << ", " << action.to << "}";
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const common::MergeAction &action) {
  os << "{" << action.pos << ", " << action.toValue << "}";
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const common::NewAction &action) {
  os << "{" << action.pos << ", " << action.value << "}";
  return os;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const std::vector<T> &set) {
  os << "[";
  bool first = true;
  for (const auto &t : set) {
    os << (first ? "" : ", ") << t;
    first = false;
  }
  os << "]\n";
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const common::SwipeAction &action) {
  os << "{\n  moveActions: " << action.moveActions
     << "  mergeActions: " << action.mergeActions << "}";
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const common::Actions &actions) {
  os << "{\n  moveActions: " << actions.moveActions
     << "  mergeActions: " << actions.mergeActions
     << "  newActions: " << actions.newActions << "}";
  return os;
}

}  // namespace std

#endif
