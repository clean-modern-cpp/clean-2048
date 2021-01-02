#include <doctest/doctest.h>

#include <memory>
#include <sstream>

#include "Game.h"
#include "common/ModelHelper.h"
#include "use_case/Random.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const use_case::GameData &gameData) {
  os << "{" << gameData.bestScore << ", " << gameData.score << ", "
     << gameData.isGameOver << ", " << gameData.rows << ", " << gameData.cols
     << ", " << gameData.newActions << "}";
  return os;
}

}  // namespace std

std::ostringstream oss;

template <bool GameOver>
class BoardMockup {
 public:
  BoardMockup() { oss << "Board::Board()\n"; }
  BoardMockup(common::Index rows, common::Index cols,
              common::NewActions newActions) {
    oss << "Board::Board(" << rows << ", " << cols << ", " << newActions
        << ")\n";
  }
  common::Index getRows() const {
    constexpr common::Index rows = 4;
    oss << "Board::getRows() -> " << rows << "\n";
    return rows;
  }
  common::Index getCols() const {
    constexpr common::Index cols = 4;
    oss << "Board::getCols() -> " << cols << "\n";
    return cols;
  }
  common::Positions emptyPositions() const {
    const auto positions =
        firstEmptyPositionsCall
            ? common::Positions{{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}}
            : common::Positions{{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}};
    firstEmptyPositionsCall = false;
    oss << "Board::emptyPositions()"
        << " -> " << positions << "\n";
    return positions;
  }
  bool isGameOver() const {
    oss << "Board::isGameOver() -> " << GameOver << "\n";
    return GameOver;
  }
  void clear() { oss << "Board::clear()\n"; }
  common::NewAction addCell(common::Position pos, common::Value value) {
    common::NewAction newAction{pos, value};
    oss << "Board::addCell(" << pos << ", " << value << "}) -> " << newAction
        << "\n";
    return newAction;
  }
  common::SwipeAction swipe(common::Direction d) {
    common::SwipeAction action{{{{0, 0}, {1, 1}}}, {{{2, 2}, 8}}};
    oss << "Board::swipe(" << d << ") -> " << action << "\n";
    return action;
  }
  common::NewActions restoreActions() const {
    common::NewActions actions{{{0, 0}, 1}, {{0, 1}, 2}};
    oss << "Board::restoreActions() -> " << actions << "\n";
    return actions;
  }

 private:
  mutable bool firstEmptyPositionsCall = true;
};

class ScoreMockup {
 public:
  ScoreMockup() = default;
  ScoreMockup(int score, int bestScore) {
    oss << "Score::Score(" << score << ", " << bestScore << ")\n";
  }
  int getScore() const {
    constexpr int score = 10;
    oss << "Score::getScore() -> " << score << "\n";
    return score;
  }
  int getBestScore() const {
    constexpr int bestScore = 100;
    oss << "Score::getBestScore() -> " << bestScore << "\n";
    return bestScore;
  }
  void update(const common::SwipeAction &action) {
    oss << "Score::update(" << action << ")\n";
  }
};

class BoardPresenterMockup : public use_case::BoardPresenter {
 public:
  void initWithDimension(int rows, int cols) override {
    oss << "BoardPresenter::initWithDimension(" << rows << ", " << cols
        << ")\n";
  }
  void present(common::Actions actions) override {
    oss << "BoardPresenter::present(" << actions << ")\n";
  }
};

class ScorePresenterMockup : public use_case::ScorePresenter {
 public:
  void present(int score, int bestScore) override {
    oss << "ScorePresenter::present(" << score << ", " << bestScore << ")\n";
  }
};

class GameOverPresenterMockup : public use_case::GameOverPresenter {
 public:
  void present() override { oss << "GameOverPresenter::present()\n"; }
};

class RandomMockup : public use_case::Random {
 public:
  int next(int min, int max) override {
    REQUIRE(index < values.size());
    oss << "Random::next(" << min << ", " << max << ")"
        << " -> " << values[index] << "\n";
    return values[index++];
  }

 private:
  int index = 0;
  inline static std::vector<int> values{2, 5, 1, 1};
};

template <bool GameOver>
class StorageMockup : public use_case::Storage {
 public:
  use_case::GameData loadGame() override {
    auto gameData = GameOver ? use_case::GameData{}
                             : use_case::GameData{100,
                                                  10,
                                                  false,
                                                  4,
                                                  4,
                                                  {
                                                      {{0, 1}, 2},
                                                  }};
    oss << "Storage::loadGame() -> " << gameData << "\n";
    return gameData;
  }
  void saveGame(const use_case::GameData &gameData) override {
    oss << "Storage::saveGame(" << gameData << ")\n";
  }
  void clear() override { oss << "Storage::clear()\n"; }
};

template <bool GameOver>
struct Tester {
  Tester() {
    oss = std::ostringstream{};
    game.setBoardPresenter(&boardPresenter);
    game.setScorePresenter(&scorePresenter);
    game.setGameOverPresenter(&gameOverPresenter);
    game.setRandom(std::make_unique<RandomMockup>());
    game.setStorage(std::make_unique<StorageMockup<GameOver>>());
  }

  use_case::Game<BoardMockup<GameOver>, ScoreMockup> game;

  BoardPresenterMockup boardPresenter;
  ScorePresenterMockup scorePresenter;
  GameOverPresenterMockup gameOverPresenter;
};

/*
 * Random of new cell:
 *   - Call Random next(0, n) for index of emptyPositions
 *   - Call Random next(1, 10) for new cell value (1/10: 4, 9/10: 2)
 */
TEST_CASE("New game") {
  Tester<false> tester;
  tester.game.newGame();
  REQUIRE_EQ(oss.str(), R"(Board::Board()
Score::getBestScore() -> 100
Score::Score(0, 100)
Board::getRows() -> 4
Board::getCols() -> 4
BoardPresenter::initWithDimension(4, 4)
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 5) -> 2
Random::next(1, 10) -> 5
Board::addCell({1, 0}, 2}) -> {{1, 0}, 2}
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 4) -> 1
Random::next(1, 10) -> 1
Board::addCell({0, 1}, 4}) -> {{0, 1}, 4}
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: [{{1, 0}, 2}, {{0, 1}, 4}]
})
Score::getScore() -> 10
Score::getBestScore() -> 100
ScorePresenter::present(10, 100)
Board::isGameOver() -> 0
)");
}

TEST_CASE("Load game") {
  Tester<false> tester;
  tester.game.loadGame();
  REQUIRE_EQ(oss.str(),
             R"(Storage::loadGame() -> {100, 10, 0, 4, 4, [{{0, 1}, 2}]}
Board::Board(4, 4, [{{0, 1}, 2}])
Score::Score(10, 100)
Board::getRows() -> 4
Board::getCols() -> 4
BoardPresenter::initWithDimension(4, 4)
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: [{{0, 1}, 2}]
})
Score::getScore() -> 10
Score::getBestScore() -> 100
ScorePresenter::present(10, 100)
Board::isGameOver() -> 0
)");
}

TEST_CASE("Load game when game is over") {
  Tester<true> tester;
  tester.game.loadGame();
  REQUIRE_EQ(oss.str(), R"(Storage::loadGame() -> {0, 0, 1, 0, 0, []}
Board::Board()
Score::getBestScore() -> 100
Score::Score(0, 100)
Board::getRows() -> 4
Board::getCols() -> 4
BoardPresenter::initWithDimension(4, 4)
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 5) -> 2
Random::next(1, 10) -> 5
Board::addCell({1, 0}, 2}) -> {{1, 0}, 2}
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 4) -> 1
Random::next(1, 10) -> 1
Board::addCell({0, 1}, 4}) -> {{0, 1}, 4}
BoardPresenter::present({
  moveActions: []
  mergeActions: []
  newActions: [{{1, 0}, 2}, {{0, 1}, 4}]
})
Score::getScore() -> 10
Score::getBestScore() -> 100
ScorePresenter::present(10, 100)
Board::isGameOver() -> 1
GameOverPresenter::present()
)");
}

TEST_CASE("Save game") {
  Tester<false> tester;
  tester.game.saveGame();
  REQUIRE_EQ(oss.str(), R"(Score::getBestScore() -> 100
Score::getScore() -> 10
Board::isGameOver() -> 0
Board::getRows() -> 4
Board::getCols() -> 4
Board::restoreActions() -> [{{0, 0}, 1}, {{0, 1}, 2}]
Storage::saveGame({100, 10, 0, 4, 4, [{{0, 0}, 1}, {{0, 1}, 2}]})
)");
}

TEST_CASE("Swipe") {
  Tester<false> tester;
  tester.game.swipe(common::Direction::left);
  REQUIRE_EQ(oss.str(), R"(Board::swipe(left) -> {
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
}
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 5) -> 2
Random::next(1, 10) -> 5
Board::addCell({1, 0}, 2}) -> {{1, 0}, 2}
Score::update({
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
})
BoardPresenter::present({
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
  newActions: [{{1, 0}, 2}]
})
Score::getScore() -> 10
Score::getBestScore() -> 100
ScorePresenter::present(10, 100)
Board::isGameOver() -> 0
)");
}

TEST_CASE("Swipe to game over") {
  Tester<true> tester;
  tester.game.swipe(common::Direction::left);
  REQUIRE_EQ(oss.str(), R"(Board::swipe(left) -> {
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
}
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 5) -> 2
Random::next(1, 10) -> 5
Board::addCell({1, 0}, 2}) -> {{1, 0}, 2}
Score::update({
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
})
BoardPresenter::present({
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
  newActions: [{{1, 0}, 2}]
})
Score::getScore() -> 10
Score::getBestScore() -> 100
ScorePresenter::present(10, 100)
Board::isGameOver() -> 1
GameOverPresenter::present()
)");
}
