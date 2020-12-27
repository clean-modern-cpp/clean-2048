#ifndef CLEAN2048_COMMON_MODEL_H_
#define CLEAN2048_COMMON_MODEL_H_

#include <unordered_set>
#include <vector>

namespace common {

using Index = int;
using Value = int;

enum class Direction { left, right, up, down };

struct Position {
  Index row;
  Index col;

  Position(Index row, Index col) : row{row}, col{col} {}
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

  MoveAction(Position from, Position to) : from{from}, to{to} {}
};

inline bool operator==(const MoveAction& lhs, const MoveAction& rhs) {
  return lhs.from == rhs.from && lhs.to == rhs.to;
}

using MoveActions = std::vector<MoveAction>;

struct NewAction {
  Position pos;
  Value value;

  NewAction(Position pos, Value value) : pos{pos}, value{value} {}
};

inline bool operator==(const NewAction& lhs, const NewAction& rhs) {
  return lhs.pos == rhs.pos && lhs.value == rhs.value;
}

using NewActions = std::vector<NewAction>;

struct ChangeAction {
  Position pos;
  Value from;
  Value to;

  ChangeAction(Position pos, Value from, Value to)
      : pos{pos}, from{from}, to{to} {}
};

inline bool operator==(const ChangeAction& lhs, const ChangeAction& rhs) {
  return lhs.pos == rhs.pos && lhs.from == rhs.from && lhs.to == rhs.to;
}

using ChangeActions = std::vector<ChangeAction>;

struct SwipeAction {
  MoveActions moveActions;
  ChangeActions changeActions;
};

struct Actions {
  MoveActions moveActions;
  NewActions newActions;
  ChangeActions changeActions;
};

}  // namespace common

#endif
