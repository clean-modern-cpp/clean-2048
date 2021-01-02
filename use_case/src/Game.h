#ifndef CLEAN2048_USECASE_GAME_H_
#define CLEAN2048_USECASE_GAME_H_

#include <spdlog/spdlog.h>

#include <memory>

#include "RandomImpl.h"
#include "common/Model.h"
#include "use_case/BoardPresenter.h"
#include "use_case/GameOverPresenter.h"
#include "use_case/GamePlayUseCase.h"
#include "use_case/GameStorageUseCase.h"
#include "use_case/ScorePresenter.h"
#include "use_case/Storage.h"

namespace use_case {

template <typename Board, typename Score>
class Game : public GamePlayUseCase, public GameStorageUseCase {
 public:
  Game() : random{std::make_unique<RandomImpl>()} {}

  void setBoardPresenter(BoardPresenter* presenter) {
    boardPresenter = presenter;
  }
  void setScorePresenter(ScorePresenter* presenter) {
    scorePresenter = presenter;
  }
  void setGameOverPresenter(GameOverPresenter* presenter) {
    gameOverPresenter = presenter;
  }

  void setRandom(std::unique_ptr<Random> r) { random = std::move(r); }
  void setStorage(std::unique_ptr<Storage> s) { storage = std::move(s); }

  void newGame() override {
    board.clear();
    if (boardPresenter) {
      boardPresenter->clearAllCells();
      boardPresenter->initWithDimension(board.getRows(), board.getCols());
    } else {
      spdlog::warn("Board presenter is nullptr");
    }

    common::Actions actions;
    actions.newActions.emplace_back(newCell());
    actions.newActions.emplace_back(newCell());
    presentAll(actions);
  }

  void startGame() override {
    if (boardPresenter) {
      boardPresenter->initWithDimension(board.getRows(), board.getCols());
    } else {
      spdlog::warn("Board presenter is nullptr");
    }
  }

  void swipe(common::Direction direction) override {
    auto swipeAction = board.swipe(direction);
    auto newActions = swipeAction.moveActions.empty()
                          ? common::NewActions{}
                          : common::NewActions{newCell()};
    score.update(swipeAction);
    presentAll({std::move(swipeAction.moveActions),
                std::move(swipeAction.mergeActions), std::move(newActions)});
  }

  void saveGame() override {
    if (storage) {
      // storage->saveScore({score.getScore(), score.getBestScore()});
      // storage->saveBoard(
      //     {board.getRows(), board.getCols(), board.restoreActions()});
    } else {
      spdlog::warn("Storage is nullptr");
    }
  }

 private:
  common::NewAction newCell() {
    const auto emptyPositions = board.emptyPositions();
    const auto pos = emptyPositions[random->next(0, emptyPositions.size() - 1)];
    const auto value = random->next(1, 10) == 1 ? 4 : 2;
    return board.addCell(pos, value);
  }

  void presentAll(common::Actions actions) {
    assert(boardPresenter);
    boardPresenter->present(std::move(actions));
    assert(scorePresenter);
    scorePresenter->present(score.getScore(), score.getBestScore());
    if (board.isGameOver()) {
      assert(gameOverPresenter);
      gameOverPresenter->present();
    }
  }

  common::NewActions loadGame() {
    assert(storage);
    // const auto scoreStorage = storage->loadScore();
    // score = Score{scoreStorage.score, scoreStorage.bestScore};
    // const auto boardStorage = storage->loadBoard();
    // board =
    //     Board{boardStorage.rows, boardStorage.cols, boardStorage.newActions};
  }

  Board board;
  Score score;

  BoardPresenter* boardPresenter = nullptr;
  ScorePresenter* scorePresenter = nullptr;
  GameOverPresenter* gameOverPresenter = nullptr;

  std::unique_ptr<Random> random;
  std::unique_ptr<Storage> storage;
};  // namespace use_case

}  // namespace use_case

#endif
