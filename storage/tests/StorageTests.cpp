#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "storage/Storage.h"

TEST_CASE("Save score") {
  storage::Storage storage;
  const use_case::ScoreStorage score{10, 100};
  storage.saveScore(score);
  const auto loadedScore = storage.loadScore();
  REQUIRE_EQ(score, loadedScore);
}

TEST_CASE("Save board") {
  storage::Storage storage;
  const use_case::BoardStorage board{2, 2, {1, 2, 3, 4}};
  storage.saveBoard(board);
  const auto loadedBoard = storage.loadBoard();
  REQUIRE_EQ(board, loadedBoard);
}
