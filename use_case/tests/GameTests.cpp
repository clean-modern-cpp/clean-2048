#include <doctest/doctest.h>

#include <memory>
#include <sstream>

#include "Game.h"
#include "common/ModelHelper.h"
#include "use_case/Random.h"

std::ostringstream oss;

class RandomMockup : public use_case::Random {
 public:
  int next(int min, int max) override {
    oss << "Random::next(" << min << ", " << max << ")";
    REQUIRE(index < values.size());
    oss << " -> " << values[index] << "\n";
    return values[index++];
  }

 private:
  int index = 0;
  inline static std::vector<int> values{2, 5, 1, 1};
};

class BoardMockup {
 public:
  BoardMockup(common::Index, common::Index) {}

  void clear() { oss << "Board::clear()\n"; }
  bool isGameOver() const { return false; }
  common::Positions emptyPositions() const {
    oss << "Board::emptyPositions()";
    static bool first = true;
    auto positions =
        first
            ? common::Positions{{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}}
            : common::Positions{{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}};
    first = false;
    oss << " -> " << positions;
    return positions;
  }
  common::NewAction addCell(common::Position pos, common::Value value) {
    oss << "Board::addCell(" << pos << ", " << value << "})\n";
    return {pos, value};
  }
  common::SwipeAction swipe(common::Direction) {
    oss << "Board::swipe()\n";
    return {
        {
            {{0, 0}, {1, 1}},
        },
        {
            {{2, 2}, 8},
        },
    };
  }
};

class ScoreMockup {
 public:
  int getScore() const {
    oss << "Score::getScore()\n";
    return 10;
  }
  int getBestScore() const {
    oss << "Score::getBestScore()\n";
    return 100;
  }

  void update(const common::SwipeAction&) { oss << "Score::update()\n"; }
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
    oss << "ScorePresenter::presenter(" << score << ", " << bestScore << ")\n";
  }
};

/*
 * Call Random next(1, 10) for new cell value (1/10: 4, 9/10: 2)
 */
TEST_CASE("New game") {
  use_case::Game<BoardMockup, ScoreMockup> game;
  BoardPresenterMockup boardPresenter;
  game.setBoardPresenter(&boardPresenter);
  ScorePresenterMockup scorePresenter;
  game.setScorePresenter(&scorePresenter);
  game.setRandom(std::make_unique<RandomMockup>());
  game.newGame();
  REQUIRE_EQ(oss.str(), R"(BoardPresenter::initWithDimension(4, 4)
Board::clear()
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 5) -> 2
Random::next(1, 10) -> 5
Board::addCell({1, 0}, 2})
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 4) -> 1
Random::next(1, 10) -> 1
Board::addCell({0, 1}, 4})
BoardPresenter::present({
  isGameOver: 0
  moveActions: []
  mergeActions: []
  newActions: [{{1, 0}, 2}, {{0, 1}, 4}]
})
Score::getScore()
Score::getBestScore()
ScorePresenter::presenter(10, 100)
)");
  oss.str("");
}

TEST_CASE("Swipe") {
  use_case::Game<BoardMockup, ScoreMockup> game;
  BoardPresenterMockup boardPresenter;
  game.setBoardPresenter(&boardPresenter);
  ScorePresenterMockup scorePresenter;
  game.setScorePresenter(&scorePresenter);
  game.setRandom(std::make_unique<RandomMockup>());
  game.swipe(common::Direction::left);
  REQUIRE_EQ(oss.str(), R"(Board::swipe()
Board::emptyPositions() -> [{0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1}]
Random::next(0, 4) -> 2
Random::next(1, 10) -> 5
Board::addCell({1, 1}, 2})
Score::update()
BoardPresenter::present({
  isGameOver: 0
  moveActions: [{{0, 0}, {1, 1}}]
  mergeActions: [{{2, 2}, 8}]
  newActions: [{{1, 1}, 2}]
})
Score::getScore()
Score::getBestScore()
ScorePresenter::presenter(10, 100)
)");
  oss.str("");
}
