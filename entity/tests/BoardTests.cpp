#include <doctest/doctest.h>

#include <algorithm>
#include <ostream>
#include <vector>

#include "common/ModelHelper.h"
#include "entity/Board.h"

inline common::Positions allPositionsOf(const entity::Board& board) {
  common::Positions positions;
  std::generate_n(std::back_inserter(positions),
                  board.getRows() * board.getCols(),
                  [cols = board.getCols(), index = 0]() mutable {
                    const common::Position pos{index / cols, index % cols};
                    ++index;
                    return pos;
                  });
  return positions;
}

inline common::Positions erase(common::Positions positions,
                               common::Position pos) {
  auto result = std::move(positions);
  result.erase(std::remove(result.begin(), result.end(), pos), result.end());
  return result;
}

struct Cell {
  common::Position pos;
  common::Value value;
};

/*
 *  4 4 4 4
 *  4 4 4 0
 *  0 2 2 2
 *  0 2 2 0
 */
const std::vector<Cell> defaultCells{
    {{0, 0}, 4}, {{0, 1}, 4}, {{0, 2}, 4}, {{0, 3}, 4},
    {{1, 0}, 4}, {{1, 1}, 4}, {{1, 2}, 4}, {{2, 1}, 2},
    {{2, 2}, 2}, {{2, 3}, 2}, {{3, 1}, 2}, {{3, 2}, 2},
};

inline void addCells(entity::Board& board,
                     const std::vector<Cell> cells = defaultCells) {
  for (const auto& cell : cells) {
    board.addCell(cell.pos, cell.value);
  }
}

/*
 *  0 0 0 0
 *  0 0 0 0
 *  0 0 0 0
 *  0 0 0 0
 */
TEST_CASE("Empty board") {
  entity::Board board;
  REQUIRE_EQ(board.getRows(), 4);
  REQUIRE_EQ(board.getCols(), 4);
  REQUIRE_EQ(board.emptyPositions(), allPositionsOf(board));
}

/*
 *  4 8 2
 *  8 0 4
 *  2 4 8
 */
TEST_CASE("Game over is false when have empty cells") {
  const common::NewActions newActions{
      {{0, 0}, 4}, {{0, 1}, 8}, {{0, 2}, 2}, {{1, 0}, 8},
      {{1, 2}, 4}, {{2, 0}, 2}, {{2, 1}, 4}, {{2, 2}, 8},
  };
  entity::Board board(3, 3, newActions);
  REQUIRE_EQ(board.isGameOver(), false);
}

/*
 *  4 8 2
 *  8 2 4
 *  2 4 4
 */
TEST_CASE("game over is false when can move") {
  const common::NewActions newActions{
      {{0, 0}, 4}, {{0, 1}, 8}, {{0, 2}, 2}, {{1, 0}, 8}, {{1, 1}, 2},
      {{1, 2}, 4}, {{2, 0}, 2}, {{2, 1}, 4}, {{2, 2}, 4},
  };
  entity::Board board(3, 3, newActions);
  REQUIRE_EQ(board.isGameOver(), false);
}

/*
 *  4  2  8  2
 *  2  8  64 4
 *  8  32 4  2
 *  2  8  2  4
 */
TEST_CASE("Game over is true") {
  const common::NewActions newActions{
      {{0, 0}, 4}, {{0, 1}, 2},  {{0, 2}, 8},  {{0, 3}, 2},
      {{1, 0}, 2}, {{1, 1}, 8},  {{1, 2}, 64}, {{1, 3}, 4},
      {{2, 0}, 8}, {{2, 1}, 32}, {{2, 2}, 4},  {{2, 3}, 2},
      {{3, 0}, 2}, {{3, 1}, 8},  {{3, 2}, 2},  {{3, 3}, 4},
  };
  entity::Board board(4, 4, newActions);
  REQUIRE_EQ(board.isGameOver(), true);
}

/*
 *  0 0 0 0
 *  0 2 0 0
 *  0 0 0 0
 *  0 0 0 0
 */
TEST_CASE("Add one cell") {
  entity::Board board;
  REQUIRE_EQ(board.addCell({1, 1}, 2), common::NewAction{{1, 1}, 2});
  const auto expectedPositions = erase(allPositionsOf(board), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 1}, 2},
                                     });
}

/*
 *  0 0 0 0
 *  0 2 0 0
 *  0 0 4 0
 *  0 0 0 0
 */
TEST_CASE("Add two cells") {
  entity::Board board;
  REQUIRE_EQ(board.addCell({1, 1}, 2), common::NewAction{{1, 1}, 2});
  REQUIRE_EQ(board.addCell({2, 2}, 4), common::NewAction{{2, 2}, 4});
  const auto expectedPositions =
      erase(erase(allPositionsOf(board), {1, 1}), {2, 2});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 1}, 2},
                                         {{2, 2}, 4},
                                     });
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
  const auto expectedPositionsBefore = erase(allPositionsOf(board), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 0}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::left), expectedAction);
  const auto expectedPositionsAfter = erase(allPositionsOf(board), {1, 0});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 0}, 2},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 3}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::right), expectedAction);
  const auto expectedPositions = erase(allPositionsOf(board), {1, 3});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 3}, 2},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {0, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::up), expectedAction);
  const auto expectedPositions = erase(allPositionsOf(board), {0, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 1}, 2},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {3, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::down), expectedAction);
  const auto expectedPositions = erase(allPositionsOf(board), {3, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{3, 1}, 2},
                                     });
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
      erase(erase(allPositionsOf(board), {1, 1}), {1, 2});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 0}},
          {{1, 2}, {1, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::left), expectedAction);
  const auto expectedPositionsAfter =
      erase(erase(allPositionsOf(board), {1, 0}), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 0}, 2},
                                         {{1, 1}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 2}, {1, 3}},
          {{1, 1}, {1, 2}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::right), expectedAction);
  const auto expectedPositions =
      erase(erase(allPositionsOf(board), {1, 2}), {1, 3});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 2}, 2},
                                         {{1, 3}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {0, 1}},
          {{2, 1}, {1, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::up), expectedAction);
  const auto expectedPositions =
      erase(erase(allPositionsOf(board), {0, 1}), {1, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 1}, 2},
                                         {{1, 1}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{2, 1}, {3, 1}},
          {{1, 1}, {2, 1}},
      },
      {},
  };
  REQUIRE_EQ(board.swipe(common::Direction::down), expectedAction);
  const auto expectedPositions =
      erase(erase(allPositionsOf(board), {2, 1}), {3, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{2, 1}, 2},
                                         {{3, 1}, 4},
                                     });
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
      erase(erase(allPositionsOf(board), {1, 1}), {1, 2});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {1, 0}},
          {{1, 2}, {1, 0}},
      },
      {
          {{1, 0}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::left), expectedAction);
  const auto expectedPositionsAfter = erase(allPositionsOf(board), {1, 0});
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 0}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 2}, {1, 3}},
          {{1, 1}, {1, 3}},
      },
      {
          {{1, 3}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::right), expectedAction);
  const auto expectedPositions = erase(allPositionsOf(board), {1, 3});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 3}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 1}, {0, 1}},
      },
      {
          {{0, 1}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::up), expectedAction);
  const auto expectedPositions = erase(allPositionsOf(board), {0, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 1}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{2, 1}, {3, 1}},
      },
      {
          {{3, 1}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::down), expectedAction);
  const auto expectedPositions = erase(allPositionsOf(board), {3, 1});
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{3, 1}, 4},
                                     });
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
  const common::Positions expectedPositionsBefore{
      {1, 3}, {2, 0}, {3, 0}, {3, 3}};
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsBefore);

  const common::SwipeAction expectedAction{
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
          {{0, 0}, 8},
          {{0, 1}, 8},
          {{1, 0}, 8},
          {{2, 0}, 4},
          {{3, 0}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::left), expectedAction);
  const common::Positions expectedPositionsAfter{
      {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {3, 1}, {3, 2}, {3, 3},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositionsAfter);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 0}, 8},
                                         {{0, 1}, 8},
                                         {{1, 0}, 8},
                                         {{1, 1}, 4},
                                         {{2, 0}, 4},
                                         {{2, 1}, 2},
                                         {{3, 0}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
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
          {{0, 3}, 8},
          {{0, 2}, 8},
          {{1, 3}, 8},
          {{2, 3}, 4},
          {{3, 3}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::right), expectedAction);
  const common::Positions expectedPositions{
      {0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {3, 0}, {3, 1}, {3, 2},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 2}, 8},
                                         {{0, 3}, 8},
                                         {{1, 2}, 4},
                                         {{1, 3}, 8},
                                         {{2, 2}, 2},
                                         {{2, 3}, 4},
                                         {{3, 3}, 4},
                                     });
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
  const common::SwipeAction expectedAction{
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
          {{0, 0}, 8},
          {{0, 1}, 8},
          {{1, 1}, 4},
          {{0, 2}, 8},
          {{1, 2}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::up), expectedAction);
  const common::Positions expectedPositions{
      {1, 0}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 0}, 8},
                                         {{0, 1}, 8},
                                         {{0, 2}, 8},
                                         {{0, 3}, 4},
                                         {{1, 1}, 4},
                                         {{1, 2}, 4},
                                         {{1, 3}, 2},
                                     });
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
  const common::SwipeAction expectedAction{
      {
          {{1, 0}, {3, 0}},
          {{0, 0}, {3, 0}},
          {{2, 1}, {3, 1}},
          {{1, 1}, {2, 1}},
          {{0, 1}, {2, 1}},
          {{2, 2}, {3, 2}},
          {{1, 2}, {2, 2}},
          {{0, 2}, {2, 2}},
          {{2, 3}, {3, 3}},
          {{0, 3}, {2, 3}},
      },
      {
          {{3, 0}, 8},
          {{3, 1}, 4},
          {{2, 1}, 8},
          {{3, 2}, 4},
          {{2, 2}, 8},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::down), expectedAction);
  const common::Positions expectedPositions{
      {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{2, 1}, 8},
                                         {{2, 2}, 8},
                                         {{2, 3}, 4},
                                         {{3, 0}, 8},
                                         {{3, 1}, 4},
                                         {{3, 2}, 4},
                                         {{3, 3}, 2},
                                     });
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  4 2 0 0          4 2 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Can not move") {
  entity::Board board;
  board.addCell({1, 0}, 4);
  board.addCell({1, 1}, 2);
  REQUIRE_EQ(board.swipe(common::Direction::left), common::SwipeAction{});
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{1, 0}, 4},
                                         {{1, 1}, 2},
                                     });
}

/*
 *  4 4 4 4 0   right  0 0 0 8 8
 *  4 4 4 0 0          0 0 0 4 8
 *  0 2 2 2 0          0 0 0 2 4
 *  0 2 2 0 0          0 0 0 0 4
 */
TEST_CASE("Board of 4 rows and 5 cols") {
  entity::Board board{4, 5, {}};
  addCells(board);
  const common::SwipeAction expectedAction{
      {
          {{0, 3}, {0, 4}},
          {{0, 2}, {0, 4}},
          {{0, 1}, {0, 3}},
          {{0, 0}, {0, 3}},
          {{1, 2}, {1, 4}},
          {{1, 1}, {1, 4}},
          {{1, 0}, {1, 3}},
          {{2, 3}, {2, 4}},
          {{2, 2}, {2, 4}},
          {{2, 1}, {2, 3}},
          {{3, 2}, {3, 4}},
          {{3, 1}, {3, 4}},
      },
      {
          {{0, 4}, 8},
          {{0, 3}, 8},
          {{1, 4}, 8},
          {{2, 4}, 4},
          {{3, 4}, 4},
      },
  };
  REQUIRE_EQ(board.swipe(common::Direction::right), expectedAction);
  const common::Positions expectedPositions{
      {0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0},
      {2, 1}, {2, 2}, {3, 0}, {3, 1}, {3, 2}, {3, 3},
  };
  REQUIRE_EQ(board.emptyPositions(), expectedPositions);
  REQUIRE_EQ(board.restoreActions(), common::NewActions{
                                         {{0, 3}, 8},
                                         {{0, 4}, 8},
                                         {{1, 3}, 4},
                                         {{1, 4}, 8},
                                         {{2, 3}, 2},
                                         {{2, 4}, 4},
                                         {{3, 4}, 4},
                                     });
}
