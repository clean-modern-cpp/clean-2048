#include <doctest/doctest.h>

#include <memory>
#include <ostream>
#include <vector>

#include "Game.h"
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
   * [ zero index of empty pos, select value 2 (2-10) or 4 (1), ...]
   */
  inline static std::vector<int> values{2, 5, 5, 1};
};

TEST_CASE("New game") {
  use_case::Game game;
  game.setRandom(std::make_unique<RandomMockup>());
  REQUIRE_EQ(game.newGame(), use_case::Actions{
                                 {},
                                 {
                                     {{0, 2}, 2},
                                     {{1, 2}, 4},
                                 },
                                 {},
                             });
}
