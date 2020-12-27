#include <doctest/doctest.h>

#include <memory>

#include "Game.h"
#include "common/ModelHelper.h"
#include "use_case/Random.h"

class RandomMockup : public use_case::Random {
 public:
  int next(int, int) override {
    CHECK(index < values.size());
    return values[index++];
  }

 private:
  int index = 0;
  /*
   * [ zero index of empty pos, select value 2 (2-10) or 4 (1), ... ]
   */
  inline static std::vector<int> values{2, 5, 1, 1};
};

class BoardMockup {
 public:
  void clear() {
    REQUIRE_EQ(step, 0);
    ++step;
  }
  common::Positions emptyPositions() const {
    switch (step) {
      case 1:
        ++step;
        return {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1},
        };
      case 3:
        ++step;
        return {
            {0, 0}, {0, 1}, {1, 1}, {2, 0}, {2, 1},
        };
      default:
        REQUIRE(false);
        return {};
    }
  }
  common::NewAction addCell(common::Position pos, common::Value value) {
    switch (step) {
      case 2:
        ++step;
        REQUIRE_EQ(pos, common::Position{1, 0});
        REQUIRE_EQ(value, 2);
        return {{1, 0}, 2};
      case 4:
        ++step;
        REQUIRE_EQ(pos, common::Position{0, 1});
        REQUIRE_EQ(value, 4);
        return {{0, 1}, 4};
      default:
        REQUIRE(false);
        return {{0, 0}, 0};
    }
  }
  common::SwipeAction swipe(common::Direction) { return {{}, {}}; }

 private:
  mutable int step = 0;
};

class BoardPresenterMockup : public use_case::BoardPresenter {
 public:
  void initWithDimension(int, int) const override {}
  void present(common::Actions actions) const override {
    REQUIRE_EQ(actions, common::Actions{
                            {},
                            {
                                {{1, 0}, 2},
                                {{0, 1}, 4},
                            },
                            {},
                        });
  }
};

TEST_CASE("New game") {
  use_case::Game<BoardMockup> game;
  BoardPresenterMockup boardPresenter;
  game.setBoardPresenter(&boardPresenter);
  game.setRandom(std::make_unique<RandomMockup>());
  game.newGame();
}
