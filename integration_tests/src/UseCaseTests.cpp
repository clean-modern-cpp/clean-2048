#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <memory>
#include <sstream>

#include "common/ModelHelper.h"
#include "use_case/Facade.h"
#include "use_case_interface/BoardPresenter.h"
#include "use_case_interface/GameOverPresenter.h"
#include "use_case_interface/Random.h"
#include "use_case_interface/ScorePresenter.h"
#include "use_case_interface/Storage.h"

namespace std {

std::ostream& operator<<(std::ostream& os,
                         const use_case_interface::GameData& gameData) {
  os << "{" << gameData.bestScore << ", " << gameData.score << ", "
     << gameData.isGameOver << ", " << gameData.rows << ", " << gameData.cols
     << ", " << gameData.newActions << "}";
  return os;
}

}  // namespace std

std::ostringstream oss;

class BoardPresenterMockup : public use_case_interface::BoardPresenter {
 public:
  void initWithDimension(int rows, int cols) override {
    oss << "BoardPresenter::initWithDimension(" << rows << ", " << cols
        << ")\n";
  }
  void present(common::Actions actions) override {
    oss << "BoardPresenter::present(" << actions << ")\n";
  }
};

class ScorePresenterMockup : public use_case_interface::ScorePresenter {
 public:
  void present(int score, int bestScore) override {
    oss << "ScorePresenter::present(" << score << ", " << bestScore << ")\n";
  }
};

class GameOverPresenterMockup : public use_case_interface::GameOverPresenter {
 public:
  void present() override { oss << "GameOverPresenter::present()\n"; }
};

class RandomMockup : public use_case_interface::Random {
 public:
  int next(int min, int max) override {
    oss << "Random::next(" << min << ", " << max << ")"
        << " -> " << values[index] << "\n";
    const auto value = values[index];
    index = (index + 1) % values.size();
    return value;
  }

 private:
  int index = 0;
  inline static std::vector<int> values{0, 2, 0, 1};
};

class StorageMockup : public use_case_interface::Storage {
 public:
  use_case_interface::GameData loadGame() override {
    use_case_interface::GameData gameData{};
    oss << "Storage::loadGame() -> " << gameData << "\n";
    return gameData;
  }
  void saveGame(const use_case_interface::GameData& gameData) override {
    oss << "Storage::saveGame(" << gameData << ")\n";
  }
  void clear() override { oss << "Storage::clear()\n"; }
};

struct Tester {
  Tester() {
    oss = std::ostringstream{};
    gamePlay = use_case::getGamePlay();
    gameStorage = use_case::getGameStorage();
    use_case::setBoardPresenter(&boardPresenter);
    use_case::setScorePresenter(&scorePresenter);
    use_case::setGameOverPresenter(&gameOverPresenter);
    use_case::setRandom(std::make_unique<RandomMockup>());
    use_case::setStorage(std::make_unique<StorageMockup>());
  }

  use_case_interface::GamePlay* gamePlay;
  use_case_interface::GameStorage* gameStorage;

  BoardPresenterMockup boardPresenter;
  ScorePresenterMockup scorePresenter;
  GameOverPresenterMockup gameOverPresenter;
};

TEST_CASE("Game play") {
  Tester tester;
  tester.gameStorage->loadGame();
  for (auto index = 0; index < 38; ++index) {
    tester.gamePlay->swipe(common::Direction::left);
    tester.gamePlay->swipe(common::Direction::right);
    tester.gamePlay->swipe(common::Direction::up);
    tester.gamePlay->swipe(common::Direction::down);
  }
  const auto result = oss.str();
  std::cout << result << std::endl;
  const std::string prefix = R"(Storage::loadGame() -> {0, 0, 1, 0, 0, []}
BoardPresenter::initWithDimension(4, 4)
Random::next(0, 15) -> 0
Random::next(1, 10) -> 2
Random::next(0, 14) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: [{{0, 0}, 2}, {{0, 1}, 4}]
})
ScorePresenter::present(0, 0)
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: []
})
ScorePresenter::present(0, 0)
Random::next(0, 13) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{0, 1}, {0, 3}}, {{0, 0}, {0, 2}}]
  mergeActions: []
  newActions: [{{0, 0}, 2}]
})
ScorePresenter::present(0, 0)
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: []
})
ScorePresenter::present(0, 0)
Random::next(0, 12) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{0, 3}, {3, 3}}, {{0, 2}, {3, 2}}, {{0, 0}, {3, 0}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(0, 0)
Random::next(0, 12) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{3, 2}, {3, 0}}, {{3, 3}, {3, 1}}]
  mergeActions: [{{3, 0}, 4}]
  newActions: [{{0, 1}, 2}]
})
ScorePresenter::present(4, 4)
Random::next(0, 12) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{0, 1}, {0, 3}}, {{0, 0}, {0, 2}}, {{3, 1}, {3, 3}}, {{3, 0}, {3, 3}}]
  mergeActions: [{{3, 3}, 8}]
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(12, 12)
Random::next(0, 11) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{3, 3}, {1, 3}}]
  mergeActions: []
  newActions: [{{0, 1}, 2}]
})
ScorePresenter::present(12, 12)
Random::next(0, 10) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{1, 3}, {3, 3}}, {{0, 3}, {2, 3}}, {{0, 2}, {3, 2}}, {{0, 1}, {3, 1}}, {{0, 0}, {3, 0}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(12, 12)
Random::next(0, 9) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{2, 3}, {2, 0}}]
  mergeActions: []
  newActions: [{{0, 1}, 2}]
})
ScorePresenter::present(12, 12)
Random::next(0, 8) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{0, 1}, {0, 3}}, {{0, 0}, {0, 2}}, {{2, 0}, {2, 3}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(12, 12)
Random::next(0, 10) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{3, 0}, {0, 0}}, {{3, 1}, {0, 1}}, {{3, 2}, {0, 2}}, {{2, 3}, {0, 3}}, {{3, 3}, {1, 3}}]
  mergeActions: [{{0, 0}, 8}, {{0, 2}, 8}, {{0, 3}, 4}]
  newActions: [{{1, 0}, 2}]
})
ScorePresenter::present(32, 32)
Random::next(0, 9) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{1, 3}, {3, 3}}, {{0, 3}, {2, 3}}, {{0, 2}, {3, 2}}, {{0, 1}, {3, 1}}, {{1, 0}, {3, 0}}, {{0, 0}, {2, 0}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(32, 32)
Random::next(0, 10) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{2, 3}, {2, 1}}, {{3, 1}, {3, 0}}, {{3, 2}, {3, 1}}, {{3, 3}, {3, 1}}]
  mergeActions: [{{3, 0}, 4}, {{3, 1}, 16}]
  newActions: [{{0, 1}, 2}]
})
ScorePresenter::present(52, 52)
Random::next(0, 9) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{0, 1}, {0, 3}}, {{0, 0}, {0, 2}}, {{2, 1}, {2, 3}}, {{2, 0}, {2, 2}}, {{3, 1}, {3, 3}}, {{3, 0}, {3, 2}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(52, 52)
Random::next(0, 8) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{2, 2}, {1, 2}}, {{3, 2}, {2, 2}}, {{2, 3}, {1, 3}}, {{3, 3}, {2, 3}}]
  mergeActions: []
  newActions: [{{0, 1}, 2}]
})
ScorePresenter::present(52, 52)
Random::next(0, 7) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{2, 3}, {3, 3}}, {{1, 3}, {2, 3}}, {{0, 3}, {1, 3}}, {{2, 2}, {3, 2}}, {{1, 2}, {2, 2}}, {{0, 2}, {1, 2}}, {{0, 1}, {3, 1}}, {{0, 0}, {3, 0}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(52, 52)
Random::next(0, 6) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{1, 2}, {1, 0}}, {{1, 3}, {1, 1}}, {{2, 2}, {2, 0}}, {{2, 3}, {2, 1}}]
  mergeActions: []
  newActions: [{{0, 1}, 2}]
})
ScorePresenter::present(52, 52)
Random::next(0, 5) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{0, 1}, {0, 3}}, {{0, 0}, {0, 2}}, {{1, 1}, {1, 3}}, {{1, 0}, {1, 2}}, {{2, 1}, {2, 3}}, {{2, 0}, {2, 2}}]
  mergeActions: []
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(52, 52)
Random::next(0, 7) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{3, 0}, {0, 0}}, {{3, 1}, {0, 1}}, {{1, 2}, {0, 2}}, {{2, 2}, {1, 2}}, {{3, 2}, {2, 2}}, {{1, 3}, {0, 3}}, {{2, 3}, {1, 3}}, {{3, 3}, {2, 3}}]
  mergeActions: [{{0, 0}, 8}, {{0, 2}, 8}, {{0, 3}, 4}]
  newActions: [{{1, 0}, 2}]
})
ScorePresenter::present(72, 72)
Random::next(0, 8) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{2, 3}, {3, 3}}, {{1, 3}, {2, 3}}, {{0, 3}, {2, 3}}, {{2, 2}, {3, 2}}, {{1, 2}, {2, 2}}, {{0, 2}, {2, 2}}, {{0, 1}, {3, 1}}, {{1, 0}, {3, 0}}, {{0, 0}, {2, 0}}]
  mergeActions: [{{2, 3}, 8}, {{2, 2}, 16}]
  newActions: [{{0, 0}, 4}]
})
)";
  REQUIRE(std::equal(prefix.cbegin(), prefix.cend(), result.cbegin()));
  const std::string surfix = R"(ScorePresenter::present(1636, 1636)
Random::next(0, 0) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{2, 1}, {2, 0}}, {{2, 2}, {2, 1}}, {{2, 3}, {2, 2}}]
  mergeActions: [{{2, 0}, 16}]
  newActions: [{{2, 3}, 4}]
})
ScorePresenter::present(1652, 1652)
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: []
})
ScorePresenter::present(1652, 1652)
Random::next(0, 1) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{2, 0}, {1, 0}}, {{3, 0}, {2, 0}}, {{3, 3}, {2, 3}}]
  mergeActions: [{{1, 0}, 32}, {{2, 3}, 8}]
  newActions: [{{3, 0}, 2}]
})
ScorePresenter::present(1692, 1692)
Random::next(0, 1) -> 0
Random::next(1, 10) -> 1
BoardPresenter::present({
  moveActions: [{{2, 3}, {3, 3}}, {{1, 3}, {2, 3}}, {{0, 3}, {1, 3}}, {{2, 0}, {3, 0}}, {{1, 0}, {2, 0}}, {{0, 0}, {1, 0}}]
  mergeActions: [{{3, 0}, 4}]
  newActions: [{{0, 0}, 4}]
})
ScorePresenter::present(1696, 1696)
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: []
})
ScorePresenter::present(1696, 1696)
Random::next(0, 0) -> 0
Random::next(1, 10) -> 2
BoardPresenter::present({
  moveActions: [{{0, 2}, {0, 3}}, {{0, 1}, {0, 2}}, {{0, 0}, {0, 1}}]
  mergeActions: []
  newActions: [{{0, 0}, 2}]
})
ScorePresenter::present(1696, 1696)
GameOverPresenter::present()
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: []
})
ScorePresenter::present(1696, 1696)
GameOverPresenter::present()
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: []
})
ScorePresenter::present(1696, 1696)
GameOverPresenter::present()
)";
  REQUIRE(std::equal(surfix.crbegin(), surfix.crend(), result.crbegin()));
}
