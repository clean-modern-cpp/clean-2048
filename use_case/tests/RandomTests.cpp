#include <doctest/doctest.h>

#include <unordered_map>

#include "RandomImpl.h"

TEST_CASE("Next random") {
  constexpr int numberCount = 10;
  constexpr int min = 1;
  constexpr int max = min + numberCount - 1;
  constexpr int randomCount = 100000;
  use_case::RandomImpl random;

  std::unordered_map<int, int> counts;
  for (int i = 0; i < randomCount; ++i) {
    counts[random.next(min, max)]++;
  }
  REQUIRE_EQ(counts.size(), numberCount);
  for (const auto& [key, value] : counts) {
    REQUIRE((key >= min && key <= max));
    CHECK(std::abs(value - randomCount / numberCount) < 500);
  }
}
