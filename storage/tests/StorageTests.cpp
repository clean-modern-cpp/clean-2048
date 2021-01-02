#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <ostream>

#include "common/ModelHelper.h"
#include "storage/Storage.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const use_case::GameData &gameData) {
  os << "{" << gameData.bestScore << ", " << gameData.score << ", "
     << gameData.isGameOver << ", " << gameData.rows << ", " << gameData.cols
     << ", " << gameData.newActions << "}";
  return os;
}

}  // namespace std

TEST_CASE("Default game storage") {
  storage::Storage storage;
  storage.clear();
  const auto gameData = storage.loadGame();
  REQUIRE_EQ(gameData.bestScore, 0);
  REQUIRE_EQ(gameData.score, 0);
  REQUIRE(gameData.isGameOver);
}

TEST_CASE("Save and load game") {
  storage::Storage storage;
  const use_case::GameData gameData{
      100,
      10,
      false,
      2,
      2,
      {
          {{0, 0}, 1},
          {{0, 1}, 2},
          {{1, 0}, 3},
          {{1, 1}, 4},
      },
  };
  storage.saveGame(gameData);
  REQUIRE_EQ(storage.loadGame(), gameData);
}
