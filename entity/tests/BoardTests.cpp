#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithm>
#include <vector>

#include "entity/Board.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const entity::Position &position) {
  os << "{" << position.row << ", " << position.column << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const entity::MoveAction &moveAction) {
  os << "{" << moveAction.from << ", " << moveAction.to << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const entity::ChangeAction &changeAction) {
  os << "{{" << changeAction.pos.row << ", " << changeAction.pos.column << "}, "
     << changeAction.from << ", " << changeAction.to << "}";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
  os << "[\n";
  for (const auto &t : vector) {
    os << t << ", ";
  }
  os << "]\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const entity::SwipeAction &action) {
  os << "{\nmoveActions: " << action.moveActions
     << "\nchangeActions: " << action.changeActions;
  return os;
}

}  // namespace std

inline entity::Positions allPositions(entity::Index size) {
  entity::Positions positions;
  std::generate_n(std::back_inserter(positions), size * size,
                  [&, index = 0]() mutable {
                    const entity::Position pos{index / size, index % size};
                    ++index;
                    return pos;
                  });
  return positions;
}

inline entity::Positions erase(entity::Positions positions,
                               entity::Position pos) {
  auto result = std::move(positions);
  result.erase(std::remove(result.begin(), result.end(), pos), result.end());
  return result;
}

/*
 *  4 4 4 4
 *  4 4 4 0
 *  0 2 2 2
 *  0 2 2 0
 */
inline void addCells(entity::Board &board) {
  struct Cell {
    entity::Position pos;
    entity::Value value;
  };
  const std::vector<Cell> cells{
      {{0, 0}, 4}, {{0, 1}, 4}, {{0, 2}, 4}, {{0, 3}, 4},
      {{1, 0}, 4}, {{1, 1}, 4}, {{1, 2}, 4}, {{2, 1}, 2},
      {{2, 2}, 2}, {{2, 3}, 2}, {{3, 1}, 2}, {{3, 2}, 2},
  };
  for (const auto &cell : cells) {
    board.addCell(cell.pos, cell.value);
  }
}

TEST_CASE("Empty board") {
  entity::Board board;
  REQUIRE_EQ(board.emptyPositions(), allPositions(4));
}

/*
 *  0 0 0 0
 *  0 2 0 0
 *  0 0 0 0
 *  0 0 0 0
 */
TEST_CASE("Add one cell") {
  entity::Board board;
  REQUIRE_EQ(board.addCell({1, 1}, 2), entity::NewAction{{1, 1}, 2});
  const auto expectedPositions = erase(allPositions(4), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0
 *  0 2 0 0
 *  0 0 4 0
 *  0 0 0 0
 */
TEST_CASE("Add two cells") {
  entity::Board board;
  REQUIRE_EQ(board.addCell({1, 1}, 2), entity::NewAction{{1, 1}, 2});
  REQUIRE_EQ(board.addCell({2, 2}, 4), entity::NewAction{{2, 2}, 4});
  const auto expectedPositions = erase(erase(allPositions(4), {1, 1}), {2, 2});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

TEST_CASE("Clear") {
  entity::Board board;
  REQUIRE_EQ(board.addCell({1, 1}, 2), entity::NewAction{{1, 1}, 2});
  REQUIRE_EQ(board.addCell({2, 2}, 4), entity::NewAction{{2, 2}, 4});
  board.clear();
  REQUIRE_EQ(board.emptyPositions(), allPositions(4));
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  0 2 0 0          2 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Move one cell left") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  const auto expectedPositionsBefore = erase(allPositions(4), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 0}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::left), expectedAction);
  const auto expectedPositionsAfter = erase(allPositions(4), {1, 0});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
}

/*
 *  0 0 0 0   right   0 0 0 0
 *  0 2 0 0           0 0 0 2
 *  0 0 0 0           0 0 0 0
 *  0 0 0 0           0 0 0 0
 */
TEST_CASE("Move one cell right") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 3}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::right), expectedAction);
  const auto expectedPositions = erase(allPositions(4), {1, 3});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   up   0 2 0 0
 *  0 2 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 */
TEST_CASE("Move one cell up") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {0, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::up), expectedAction);
  const auto expectedPositions = erase(allPositions(4), {0, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   down   0 0 0 0
 *  0 2 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 2 0 0
 */
TEST_CASE("Move one cell down") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {3, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::down), expectedAction);
  const auto expectedPositions = erase(allPositions(4), {3, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  0 2 4 0          2 4 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Move two cells left") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  board.addCell({1, 2}, 4);
  const auto expectedPositionsBefore =
      erase(erase(allPositions(4), {1, 1}), {1, 2});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 0}},
          {{1, 2}, {1, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::left), expectedAction);
  const auto expectedPositionsAfter =
      erase(erase(allPositions(4), {1, 0}), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
}

/*
 *  0 0 0 0   right   0 0 0 0
 *  0 2 4 0           0 0 2 4
 *  0 0 0 0           0 0 0 0
 *  0 0 0 0           0 0 0 0
 */
TEST_CASE("Move two cells right") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  board.addCell({1, 2}, 4);
  const entity::SwipeAction expectedAction{
      {
          {{1, 2}, {1, 3}},
          {{1, 1}, {1, 2}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::right), expectedAction);
  const auto expectedPositions = erase(erase(allPositions(4), {1, 2}), {1, 3});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   up   0 2 0 0
 *  0 2 0 0        0 4 0 0
 *  0 4 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 */
TEST_CASE("Move two cells up") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  board.addCell({2, 1}, 4);
  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {0, 1}},
          {{2, 1}, {1, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::up), expectedAction);
  const auto expectedPositions = erase(erase(allPositions(4), {0, 1}), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   down   0 0 0 0
 *  0 2 0 0          0 0 0 0
 *  0 4 0 0          0 2 0 0
 *  0 0 0 0          0 4 0 0
 */
TEST_CASE("Move two cells down") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  board.addCell({2, 1}, 4);
  const entity::SwipeAction expectedAction{
      {
          {{2, 1}, {3, 1}},
          {{1, 1}, {2, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(entity::Direction::down), expectedAction);
  const auto expectedPositions = erase(erase(allPositions(4), {2, 1}), {3, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  0 2 2 0          4 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Move two cells left and merge") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  board.addCell({1, 2}, 2);
  const auto expectedPositionsBefore =
      erase(erase(allPositions(4), {1, 1}), {1, 2});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 0}},
          {{1, 2}, {1, 0}},
      },
      {
          {{1, 0}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::left), expectedAction);
  const auto expectedPositionsAfter = erase(allPositions(4), {1, 0});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
}

/*
 *  0 0 0 0   right   0 0 0 0
 *  0 2 2 0           0 0 0 4
 *  0 0 0 0           0 0 0 0
 *  0 0 0 0           0 0 0 0
 */
TEST_CASE("Move two cells right and merge") {
  entity::Board board;
  board.addCell({1, 1}, 2);
  board.addCell({1, 2}, 2);
  const entity::SwipeAction expectedAction{
      {
          {{1, 2}, {1, 3}},
          {{1, 1}, {1, 3}},
      },
      {
          {{1, 3}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::right), expectedAction);
  const auto expectedPositions = erase(allPositions(4), {1, 3});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 2 0 0   up   0 4 0 0
 *  0 2 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 */
TEST_CASE("Move two cells up and merge") {
  entity::Board board;
  board.addCell({0, 1}, 2);
  board.addCell({1, 1}, 2);
  const entity::SwipeAction expectedAction{
      {
          {{1, 1}, {0, 1}},
      },
      {
          {{0, 1}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::up), expectedAction);
  const auto expectedPositions = erase(allPositions(4), {0, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  0 0 0 0   down   0 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 2 0 0          0 0 0 0
 *  0 2 0 0          0 4 0 0
 */
TEST_CASE("Move two cells up and merge") {
  entity::Board board;
  board.addCell({2, 1}, 2);
  board.addCell({3, 1}, 2);
  const entity::SwipeAction expectedAction{
      {
          {{2, 1}, {3, 1}},
      },
      {
          {{3, 1}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::down), expectedAction);
  const auto expectedPositions = erase(allPositions(4), {3, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  4 4 4 4   left   8 8 0 0
 *  4 4 4 0          8 4 0 0
 *  0 2 2 2          4 2 0 0
 *  0 2 2 0          4 0 0 0
 */
TEST_CASE("Move multi-line cells left and merge") {
  entity::Board board;
  addCells(board);
  const entity::Positions expectedPositionsBefore{
      {1, 3}, {2, 0}, {3, 0}, {3, 3}};
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const entity::SwipeAction expectedAction{
      {
          {{0, 1}, {0, 0}},
          {{0, 2}, {0, 1}},
          {{0, 3}, {0, 1}},
          {{1, 1}, {1, 0}},
          {{1, 2}, {1, 1}},
          {{2, 1}, {2, 0}},
          {{2, 2}, {2, 0}},
          {{2, 3}, {2, 1}},
          {{3, 1}, {3, 0}},
          {{3, 2}, {3, 0}},
      },
      {
          {{0, 0}, 4, 8},
          {{0, 1}, 4, 8},
          {{1, 0}, 4, 8},
          {{2, 0}, 2, 4},
          {{3, 0}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::left), expectedAction);
  const entity::Positions expectedPositionsAfter{
      {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {3, 1}, {3, 2}, {3, 3},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
}

/*
 *  4 4 4 4   right   0 0 8 8
 *  4 4 4 0           0 0 4 8
 *  0 2 2 2           0 0 2 4
 *  0 2 2 0           0 0 0 4
 */
TEST_CASE("Move multi-line cells right and merge") {
  entity::Board board;
  addCells(board);
  const entity::SwipeAction expectedAction{
      {
          {{0, 2}, {0, 3}},
          {{0, 1}, {0, 2}},
          {{0, 0}, {0, 2}},
          {{1, 2}, {1, 3}},
          {{1, 1}, {1, 3}},
          {{1, 0}, {1, 2}},
          {{2, 2}, {2, 3}},
          {{2, 1}, {2, 2}},
          {{3, 2}, {3, 3}},
          {{3, 1}, {3, 3}},
      },
      {
          {{0, 3}, 4, 8},
          {{0, 2}, 4, 8},
          {{1, 3}, 4, 8},
          {{2, 3}, 2, 4},
          {{3, 3}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::right), expectedAction);
  const entity::Positions expectedPositions{
      {0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {3, 0}, {3, 1}, {3, 2},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  4 4 4 4   up   8 8 8 4
 *  4 4 4 0        0 4 4 2
 *  0 2 2 2        0 0 0 0
 *  0 2 2 0        0 0 0 0
 */
TEST_CASE("Move multi-line cells up and merge") {
  entity::Board board;
  addCells(board);
  const entity::SwipeAction expectedAction{
      {
          {{1, 0}, {0, 0}},
          {{1, 1}, {0, 1}},
          {{2, 1}, {1, 1}},
          {{3, 1}, {1, 1}},
          {{1, 2}, {0, 2}},
          {{2, 2}, {1, 2}},
          {{3, 2}, {1, 2}},
          {{2, 3}, {1, 3}},
      },
      {
          {{0, 0}, 4, 8},
          {{0, 1}, 4, 8},
          {{1, 1}, 2, 4},
          {{0, 2}, 4, 8},
          {{1, 2}, 2, 4},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::up), expectedAction);
  const entity::Positions expectedPositions{
      {1, 0}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}

/*
 *  4 4 4 4   down   0 0 0 0
 *  4 4 4 0          0 0 0 0
 *  0 2 2 2          0 8 8 4
 *  0 2 2 0          8 4 4 2
 */
TEST_CASE("Move multi-line cells down and merge") {
  entity::Board board;
  addCells(board);
  const entity::SwipeAction expectedAction{
      {
          {{2, 3}, {3, 3}},
          {{0, 3}, {2, 3}},
          {{2, 2}, {3, 2}},
          {{1, 2}, {2, 2}},
          {{0, 2}, {2, 2}},
          {{2, 1}, {3, 1}},
          {{1, 1}, {2, 1}},
          {{0, 1}, {2, 1}},
          {{1, 0}, {3, 0}},
          {{0, 0}, {3, 0}},
      },
      {
          {{3, 2}, 2, 4},
          {{2, 2}, 4, 8},
          {{3, 1}, 2, 4},
          {{2, 1}, 4, 8},
          {{3, 0}, 4, 8},
      },
  };
  REQUIRE_EQ(board.swipe(entity::Direction::down), expectedAction);
  const entity::Positions expectedPositions{
      {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
}
