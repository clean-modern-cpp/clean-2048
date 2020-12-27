#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "common/ModelHelper.h"

TEST_CASE("Position test") {
  common::Positions positions{{0, 0}, {0, 1}};
  REQUIRE_EQ(positions.size(), 2);
  REQUIRE_EQ(positions, common::Positions{{0, 1}, {0, 0}});
}

TEST_CASE("SwipeAction test") {
  common::SwipeAction swipeAction;
  swipeAction.moveActions.emplace(common::Position{0, 0},
                                  common::Position{0, 1});
  swipeAction.moveActions.emplace(common::Position{1, 1},
                                  common::Position{3, 1});
  swipeAction.changeActions.emplace(common::Position{0, 0}, 1, 2);
  swipeAction.changeActions.emplace(common::Position{1, 1}, 2, 4);
  REQUIRE_EQ(swipeAction, common::SwipeAction{
                              {
                                  {{0, 0}, {0, 1}},
                                  {{1, 1}, {3, 1}},
                              },
                              {
                                  {{1, 1}, 2, 4},
                                  {{0, 0}, 1, 2},
                              },
                          });
}

TEST_CASE("Actions test") {
  common::Actions actions;
  actions.moveActions.emplace(common::Position{0, 0}, common::Position{0, 1});
  actions.newActions.emplace(common::Position{0, 0}, 2);
  actions.newActions.emplace(common::Position{1, 1}, 4);
  actions.changeActions.emplace(common::Position{0, 0}, 1, 2);
  REQUIRE_EQ(actions, common::Actions{
                          {
                              {{0, 0}, {0, 1}},
                          },
                          {
                              {{1, 1}, 4},
                              {{0, 0}, 2},
                          },
                          {
                              {{0, 0}, 1, 2},
                          },
                      });
}
