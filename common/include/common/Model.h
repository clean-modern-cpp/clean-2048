#ifndef CLEAN2048_COMMON_MODEL_H_
#define CLEAN2048_COMMON_MODEL_H_

#include <unordered_set>
#include <vector>

namespace common {

using Index = int;
using Value = int;
using Values = std::vector<Value>;

enum class Direction { left, right, up, down };

struct Position {
  Index row;
  Index col;
};

inline bool operator==(const Position& lhs, const Position& rhs) {
  return lhs.row == rhs.row && lhs.col == rhs.col;
}
inline bool operator!=(const Position& lhs, const Position& rhs) {
  return !(lhs == rhs);
}

using Positions = std::vector<Position>;

struct MoveAction {
  Position from;
  Position to;

  MoveAction(Position from = {}, Position to = {}) : from{from}, to{to} {}
};

inline bool operator==(const MoveAction& lhs, const MoveAction& rhs) {
  return lhs.from == rhs.from && lhs.to == rhs.to;
}

using MoveActions = std::vector<MoveAction>;

struct MergeAction {
  Position pos;
  Value toValue;

  MergeAction(Position pos = {}, Value value = 0) : pos{pos}, toValue{value} {}
};

inline bool operator==(const MergeAction& lhs, const MergeAction& rhs) {
  return lhs.pos == rhs.pos && lhs.toValue == rhs.toValue;
}

using MergeActions = std::vector<MergeAction>;

struct NewAction {
  Position pos;
  Value value;

  NewAction(Position pos = {}, Value value = 0) : pos{pos}, value{value} {}
};

inline bool operator==(const NewAction& lhs, const NewAction& rhs) {
  return lhs.pos == rhs.pos && lhs.value == rhs.value;
}

using NewActions = std::vector<NewAction>;

struct SwipeAction {
  MoveActions moveActions;
  MergeActions mergeActions;
};

struct Actions {
  MoveActions moveActions;
  MergeActions mergeActions;
  NewActions newActions;
};

}  // namespace common

#endif
