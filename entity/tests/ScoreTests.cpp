#include <doctest/doctest.h>

#include "entity/Score.h"

TEST_CASE("Update score") {
  entity::Score score;
  score.update({
      {},
      {
          {{0, 0}, 1},
          {{0, 0}, 2},
          {{0, 0}, 3},
      },
  });
  REQUIRE_EQ(score.getScore(), 6);
  REQUIRE_EQ(score.getBestScore(), 6);
}

TEST_CASE("Update score") {
  entity::Score score{0, 10};
  score.update({
      {},
      {
          {{0, 0}, 1},
          {{0, 0}, 2},
          {{0, 0}, 3},
      },
  });
  REQUIRE_EQ(score.getScore(), 6);
  REQUIRE_EQ(score.getBestScore(), 10);
  score.reset();
  REQUIRE_EQ(score.getScore(), 0);
  REQUIRE_EQ(score.getBestScore(), 10);
}
