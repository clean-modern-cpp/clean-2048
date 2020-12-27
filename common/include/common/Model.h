#ifndef CLEAN2048_COMMON_MODEL_H_
#define CLEAN2048_COMMON_MODEL_H_

#include <vector>

namespace common::model {

using Index = int;
using Value = int;

enum class Direction { left, right, up, down };

struct Position {
  Index row;
  Index column;

  Position(Index row, Index column) : row{row}, column{column} {}

  friend bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.row == rhs.row && lhs.column == rhs.column;
  }
};

using Positions = std::vector<Position>;

struct MoveAction {
  Position from;
  Position to;

  MoveAction(Position from, Position to) : from{from}, to{to} {}

  friend bool operator==(const MoveAction& lhs, const MoveAction& rhs) {
    return lhs.from == rhs.from && lhs.to == rhs.to;
  }
};

struct NewAction {
  Position pos;
  Value value;

  NewAction(Position pos, Value value) : pos{pos}, value{value} {}

  friend bool operator==(const NewAction& lhs, const NewAction& rhs) {
    return lhs.pos == rhs.pos && lhs.value == rhs.value;
  }
};

struct ChangeAction {
  Position pos;
  Value from;
  Value to;

  ChangeAction(Position pos, Value from, Value to)
      : pos{pos}, from{from}, to{to} {}

  friend bool operator==(const ChangeAction& lhs, const ChangeAction& rhs) {
    return lhs.pos == rhs.pos && lhs.from == rhs.from && lhs.to == rhs.to;
  }
};

struct Actions {
  std::vector<MoveAction> moveActions;
  std::vector<NewAction> newActions;
  std::vector<ChangeAction> changeActions;
};

}  // namespace common::model

#endif
