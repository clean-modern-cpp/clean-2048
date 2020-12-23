#ifndef CLEAN2048_COMMON_MODEL_H_
#define CLEAN2048_COMMON_MODEL_H_

#include <vector>

namespace common::model {

enum class Direction { left, right, up, down };

struct Position {
  int row;
  int column;

  friend bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.row == rhs.row && lhs.column == rhs.column;
  }

  friend bool operator!=(const Position& lhs, const Position& rhs) {
    return lhs.row != rhs.row || lhs.column != rhs.column;
  }
};

struct MoveAction {
  Position from;
  Position to;
};

struct NewAction {
  Position pos;
  int value;
};

struct DoubleAction {
  Position pos;
};

struct Actions {
  std::vector<MoveAction> moveActions;
  std::vector<NewAction> newActions;
  std::vector<DoubleAction> doubleActions;
};

}  // namespace common::model

#endif
