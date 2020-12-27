#include <doctest/doctest.h>

#include <memory>
#include <ostream>
#include <vector>

#include "Game.h"
#include "entity/Board.h"
#include "use_case/Model.h"
#include "use_case/Random.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const use_case::Position &position) {
  os << "{" << position.row << ", " << position.column << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const use_case::MoveAction &moveAction) {
  os << "{" << moveAction.from << ", " << moveAction.to << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const use_case::NewAction &changeAction) {
  os << "{{" << changeAction.pos.row << ", " << changeAction.pos.column << "}, "
     << changeAction.value << "}";
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const use_case::ChangeAction &changeAction) {
  os << "{{" << changeAction.pos.row << ", " << changeAction.pos.column << "}, "
     << changeAction.from << ", " << changeAction.to << "}";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector) {
  os << "[\n";
  for (const auto &t : vector) {
    os << t << ", ";
  }
  os << "]\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const use_case::Actions &actions) {
  os << "{\nmoveActions: " << actions.moveActions
     << "{\nnewActions: " << actions.newActions
     << "\nchangeActions: " << actions.changeActions;
  return os;
}

}  // namespace std

namespace use_case {

bool operator==(const Position &lhs, const Position &rhs) {
  return lhs.row == rhs.row && lhs.column == rhs.column;
}

bool operator==(const Actions &lhs, const Actions &rhs) {
  return lhs.newActions == rhs.newActions;
}

}  // namespace use_case

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
  use_case::Positions emptyPositions() const {
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
  use_case::NewAction addCell(use_case::Position pos, use_case::Value value) {
    switch (step) {
      case 2:
        ++step;
        REQUIRE_EQ(pos, use_case::Position{1, 0});
        REQUIRE_EQ(value, 2);
        return {{1, 0}, 2};
      case 4:
        ++step;
        REQUIRE_EQ(pos, use_case::Position{0, 1});
        REQUIRE_EQ(value, 4);
        return {{0, 1}, 4};
      default:
        REQUIRE(false);
        return {{0, 0}, 0};
    }
  }
  entity::SwipeAction swipe(use_case::Direction) { return {{}, {}}; }

 private:
  mutable int step = 0;
};

TEST_CASE("New game") {
  use_case::Game<BoardMockup> game;
  game.setRandom(std::make_unique<RandomMockup>());
  REQUIRE_EQ(game.newGame(), use_case::Actions{
                                 {},
                                 {
                                     {{1, 0}, 2},
                                     {{0, 1}, 4},
                                 },
                                 {},
                             });
}
