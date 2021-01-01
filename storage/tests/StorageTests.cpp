#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "storage/Storage.h"

TEST_CASE("Default") {
  storage::Storage storage;
  storage.clear();
  REQUIRE_EQ(storage.loadScore(), use_case::ScoreData{0, 0});
  REQUIRE_EQ(storage.loadBoard(), use_case::BoardData{4, 4, {}});
}

TEST_CASE("Save score") {
  storage::Storage storage;
  const use_case::ScoreData scoreData{10, 100};
  storage.saveScore(scoreData);
  REQUIRE_EQ(storage.loadScore(), scoreData);
}

TEST_CASE("Save board") {
  storage::Storage storage;

  const use_case::BoardData boardData{2,
                                      2,
                                      {
                                          {{0, 0}, 1},
                                          {{0, 1}, 2},
                                          {{1, 0}, 3},
                                          {{1, 1}, 4},
                                      }};
  storage.saveBoard(boardData);
  REQUIRE_EQ(storage.loadBoard(), boardData);
}
