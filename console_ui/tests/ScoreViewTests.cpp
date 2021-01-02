#include <doctest/doctest.h>

#include <string>

#include "ScoreView.h"
#include "common/Model.h"

TEST_CASE("Body of score view") {
  console_ui::ScoreView scoreView;
  scoreView.present(10, 100);
  REQUIRE_EQ(scoreView.body(), R"([ 2048 ] [ Score: 10] [Best Score: 100]
)");
}
