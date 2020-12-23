#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <vector>

#include "entity/Board.h"

TEST_CASE("Constructor") {
  entity::Board board;
  REQUIRE_EQ(board.tiles(), entity::Tiles{});
}

/*
 *  0 0 0 0
 *  0 2 0 0
 *  0 0 4 0
 *  0 0 0 0
 */
TEST_CASE("Add tiles") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{2, 2}, 4});
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 1}, 2}, {{2, 2}, 4}});
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  0 2 0 0          2 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Move one tile left") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.move(common::model::Direction::left);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 0}, 2}});
}

/*
 *  0 0 0 0   right   0 0 0 0
 *  0 2 0 0           0 0 0 2
 *  0 0 0 0           0 0 0 0
 *  0 0 0 0           0 0 0 0
 */
TEST_CASE("Move one tile right") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.move(common::model::Direction::right);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 3}, 2}});
}

/*
 *  0 0 0 0   up   0 2 0 0
 *  0 2 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 */
TEST_CASE("Move one tile up") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.move(common::model::Direction::up);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{0, 1}, 2}});
}

/*
 *  0 0 0 0   down   0 0 0 0
 *  0 2 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 2 0 0
 */
TEST_CASE("Move one tile down") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.move(common::model::Direction::down);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{3, 1}, 2}});
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  0 2 4 0          2 4 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Move two tiles left") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{1, 2}, 4});
  board.move(common::model::Direction::left);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 0}, 2}, {{1, 1}, 4}});
}

/*
 *  0 0 0 0   right   0 0 0 0
 *  0 2 4 0           0 0 2 4
 *  0 0 0 0           0 0 0 0
 *  0 0 0 0           0 0 0 0
 */
TEST_CASE("Move two tiles right") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{1, 2}, 4});
  board.move(common::model::Direction::right);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 2}, 2}, {{1, 3}, 4}});
}

/*
 *  0 0 0 0   up   0 2 0 0
 *  0 2 0 0        0 4 0 0
 *  0 4 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 */
TEST_CASE("Move two tiles up") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{2, 1}, 4});
  board.move(common::model::Direction::up);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{0, 1}, 2}, {{1, 1}, 4}});
}

/*
 *  0 0 0 0   down   0 0 0 0
 *  0 2 0 0          0 0 0 0
 *  0 4 0 0          0 2 0 0
 *  0 0 0 0          0 4 0 0
 */
TEST_CASE("Move two tiles down") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{2, 1}, 4});
  board.move(common::model::Direction::down);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{2, 1}, 2}, {{3, 1}, 4}});
}

/*
 *  0 0 0 0   left   0 0 0 0
 *  0 2 2 0          4 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 0 0 0          0 0 0 0
 */
TEST_CASE("Move two tiles left and merge") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{1, 2}, 2});
  board.move(common::model::Direction::left);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 0}, 4}});
}

/*
 *  0 0 0 0   right   0 0 0 0
 *  0 2 2 0           0 0 0 4
 *  0 0 0 0           0 0 0 0
 *  0 0 0 0           0 0 0 0
 */
TEST_CASE("Move two tiles right and merge") {
  entity::Board board;
  board.addTile({{1, 1}, 2});
  board.addTile({{1, 2}, 2});
  board.move(common::model::Direction::right);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{1, 3}, 4}});
}

/*
 *  0 2 0 0   up   0 4 0 0
 *  0 2 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 *  0 0 0 0        0 0 0 0
 */
TEST_CASE("Move two tiles up and merge") {
  entity::Board board;
  board.addTile({{0, 1}, 2});
  board.addTile({{1, 1}, 2});
  board.move(common::model::Direction::up);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{0, 1}, 4}});
}

/*
 *  0 0 0 0   down   0 0 0 0
 *  0 0 0 0          0 0 0 0
 *  0 2 0 0          0 0 0 0
 *  0 2 0 0          0 4 0 0
 */
TEST_CASE("Move two tiles up and merge") {
  entity::Board board;
  board.addTile({{2, 1}, 2});
  board.addTile({{3, 1}, 2});
  board.move(common::model::Direction::down);
  REQUIRE_EQ(board.tiles(), entity::Tiles{{{3, 1}, 4}});
}

/*
 *  4 4 4 4   left   8 8 0 0
 *  4 4 4 0          8 4 0 0
 *  0 2 2 2          4 2 0 0
 *  0 2 2 0          4 0 0 0
 */
TEST_CASE("Move multi-line tiles left and merge") {
  entity::Board board;
  const std::vector<entity::Tile> tiles{
      {{0, 0}, 4}, {{0, 1}, 4}, {{0, 2}, 4}, {{0, 3}, 4},
      {{1, 0}, 4}, {{1, 1}, 4}, {{1, 2}, 4}, {{2, 1}, 2},
      {{2, 2}, 2}, {{2, 3}, 2}, {{3, 1}, 2}, {{3, 2}, 2},
  };
  for (const auto &tile : tiles) {
    board.addTile(tile);
  }
  board.move(common::model::Direction::left);
  const std::vector<entity::Tile> expectedTiles = {
      {{0, 0}, 8}, {{0, 1}, 8}, {{1, 0}, 8}, {{1, 1}, 4},
      {{2, 0}, 4}, {{2, 1}, 2}, {{3, 0}, 4},
  };
  REQUIRE_EQ(board.tiles(), expectedTiles);
}

/*
 *  4 4 4 4   right   0 0 8 8
 *  4 4 4 0           0 0 4 8
 *  0 2 2 2           0 0 2 4
 *  0 2 2 0           0 0 0 4
 */
TEST_CASE("Move multi-line tiles right and merge") {
  entity::Board board;
  const std::vector<entity::Tile> tiles{
      {{0, 0}, 4}, {{0, 1}, 4}, {{0, 2}, 4}, {{0, 3}, 4},
      {{1, 0}, 4}, {{1, 1}, 4}, {{1, 2}, 4}, {{2, 1}, 2},
      {{2, 2}, 2}, {{2, 3}, 2}, {{3, 1}, 2}, {{3, 2}, 2},
  };
  for (const auto &tile : tiles) {
    board.addTile(tile);
  }
  board.move(common::model::Direction::right);
  const std::vector<entity::Tile> expectedTiles = {
      {{0, 2}, 8}, {{0, 3}, 8}, {{1, 2}, 4}, {{1, 3}, 8},
      {{2, 2}, 2}, {{2, 3}, 4}, {{3, 3}, 4},
  };
  REQUIRE_EQ(board.tiles(), expectedTiles);
}

/*
 *  4 4 4 4   up   8 8 8 4
 *  4 4 4 0        0 4 4 2
 *  0 2 2 2        0 0 0 0
 *  0 2 2 0        0 0 0 0
 */
TEST_CASE("Move multi-line tiles up and merge") {
  entity::Board board;
  const std::vector<entity::Tile> tiles{
      {{0, 0}, 4}, {{0, 1}, 4}, {{0, 2}, 4}, {{0, 3}, 4},
      {{1, 0}, 4}, {{1, 1}, 4}, {{1, 2}, 4}, {{2, 1}, 2},
      {{2, 2}, 2}, {{2, 3}, 2}, {{3, 1}, 2}, {{3, 2}, 2},
  };
  for (const auto &tile : tiles) {
    board.addTile(tile);
  }
  board.move(common::model::Direction::up);
  const std::vector<entity::Tile> expectedTiles = {
      {{0, 0}, 8}, {{0, 1}, 8}, {{0, 2}, 8}, {{0, 3}, 4},
      {{1, 1}, 4}, {{1, 2}, 4}, {{1, 3}, 2},
  };
  REQUIRE_EQ(board.tiles(), expectedTiles);
}

/*
 *  4 4 4 4   down   0 0 0 0
 *  4 4 4 0          0 0 0 0
 *  0 2 2 2          0 8 8 4
 *  0 2 2 0          8 4 4 2
 */
TEST_CASE("Move multi-line tiles down and merge") {
  entity::Board board;
  const std::vector<entity::Tile> tiles{
      {{0, 0}, 4}, {{0, 1}, 4}, {{0, 2}, 4}, {{0, 3}, 4},
      {{1, 0}, 4}, {{1, 1}, 4}, {{1, 2}, 4}, {{2, 1}, 2},
      {{2, 2}, 2}, {{2, 3}, 2}, {{3, 1}, 2}, {{3, 2}, 2},
  };
  for (const auto &tile : tiles) {
    board.addTile(tile);
  }
  board.move(common::model::Direction::down);
  const std::vector<entity::Tile> expectedTiles = {
      {{2, 1}, 8}, {{2, 2}, 8}, {{2, 3}, 4}, {{3, 0}, 8},
      {{3, 1}, 4}, {{3, 2}, 4}, {{3, 3}, 2},
  };
  REQUIRE_EQ(board.tiles(), expectedTiles);
}
