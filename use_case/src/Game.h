#ifndef CLEAN2048_USECASE_GAME_H_
#define CLEAN2048_USECASE_GAME_H_

#include <memory>

#include "RandomImpl.h"
#include "common/Model.h"
#include "use_case/BoardPresenter.h"
#include "use_case/GamePlay.h"

namespace use_case {

template <typename Board>
class Game : public GamePlay {
 public:
  Game() : random{std::make_unique<RandomImpl>()} {}

  void setBoardPresenter(BoardPresenter* presenter) {
    boardPresenter = presenter;
  }
  void setRandom(std::unique_ptr<Random> r) { random = std::move(r); }

  void newGame() override {
    if (boardPresenter) {
      boardPresenter->initWithDimension(4, 4);
    }
    board.clear();
    common::Actions actions;
    actions.newActions.push_back(newCell());
    actions.newActions.push_back(newCell());
    if (boardPresenter) {
      boardPresenter->present(actions);
    }
  }

  void swipe(common::Direction direction) override {
    auto swipeAction = board.swipe(direction);
    auto newActions = swipeAction.moveActions.empty()
                          ? common::NewActions{}
                          : common::NewActions{newCell()};
    if (boardPresenter) {
      boardPresenter->present({std::move(swipeAction.moveActions),
                               std::move(newActions),
                               std::move(swipeAction.changeActions)});
    }
  }

 private:
  common::NewAction newCell() {
    const auto emptyPositions = board.emptyPositions();
    const auto pos = emptyPositions[random->next(0, emptyPositions.size() - 1)];
    const auto value = random->next(1, 10) == 1 ? 4 : 2;
    return board.addCell(pos, value);
  }

  Board board;

  BoardPresenter* boardPresenter = nullptr;

  std::unique_ptr<Random> random;
};

}  // namespace use_case

#endif
