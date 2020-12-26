#include <doctest/doctest.h>

#include <unordered_map>

#include "RandomImpl.h"

TEST_CASE("Next random") {
  constexpr int min = 1;
  constexpr int max = 10;
  constexpr int randomCount = 100000;
  std::unordered_map<int, int> counts;
  use_case::RandomImpl random;
  for (int i = 0; i < randomCount; ++i) {
    auto result = random.next(min, max);
    counts[result]++;
  }
  REQUIRE_EQ(counts.size(), max - min + 1);
  for (const auto& [key, value] : counts) {
    CHECK(std::abs(value - randomCount / (max - min + 1)) <
          randomCount / (max - min + 1) / 10);
  }
}
