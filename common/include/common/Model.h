#ifndef CLEAN2048_COMMON_MODEL_H_
#define CLEAN2048_COMMON_MODEL_H_

#include <unordered_set>

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

struct HashPosition {
  std::size_t operator()(const Position& pos) const {
    return std::hash<Index>{}(pos.row) ^ (std::hash<Index>{}(pos.col) < 1);
  }
};

using Positions = std::unordered_set<Position, HashPosition>;

struct MoveAction {
  Position from;
  Position to;

  MoveAction(Position from, Position to) : from{from}, to{to} {}
};

inline bool operator==(const MoveAction& lhs, const MoveAction& rhs) {
  return lhs.from == rhs.from && lhs.to == rhs.to;
}

struct HashMoveAction {
  std::size_t operator()(const MoveAction& moveAction) const {
    return HashPosition{}(moveAction.from) ^
           (HashPosition{}(moveAction.to) < 1);
  }
};

using MoveActions = std::unordered_set<MoveAction, HashMoveAction>;

struct NewAction {
  Position pos;
  Value value;

  NewAction(Position pos, Value value) : pos{pos}, value{value} {}
};

inline bool operator==(const NewAction& lhs, const NewAction& rhs) {
  return lhs.pos == rhs.pos && lhs.value == rhs.value;
}

struct HashNewAction {
  std::size_t operator()(const NewAction& newAction) const {
    return HashPosition{}(newAction.pos) ^
           (std::hash<Value>{}(newAction.value) < 1);
  }
};

using NewActions = std::unordered_set<NewAction, HashNewAction>;

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

struct HashChangeAction {
  std::size_t operator()(const ChangeAction& changeAction) const {
    return HashPosition{}(changeAction.pos) ^
           (std::hash<Value>{}(changeAction.from) < 1) ^
           (std::hash<Value>{}(changeAction.to) < 2);
  }
};

using ChangeActions = std::unordered_set<ChangeAction, HashChangeAction>;

struct SwipeAction {
  MoveActions moveActions;
  ChangeActions changeActions;
};

inline bool operator==(const SwipeAction& lhs, const SwipeAction& rhs) {
  return lhs.moveActions == rhs.moveActions &&
         lhs.changeActions == rhs.changeActions;
}

struct Actions {
  MoveActions moveActions;
  NewActions newActions;
  ChangeActions changeActions;
};

inline bool operator==(const Actions& lhs, const Actions& rhs) {
  return lhs.moveActions == rhs.moveActions &&
         lhs.newActions == rhs.newActions &&
         lhs.changeActions == rhs.changeActions;
}

}  // namespace common

#endif
