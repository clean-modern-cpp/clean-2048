#ifndef CLEAN2048_USECASE_GAME_H_
#define CLEAN2048_USECASE_GAME_H_

#include <cassert>
#include <memory>

#include "RandomImpl.h"
#include "common/Model.h"
#include "use_case/BoardPresenter.h"
#include "use_case/GameOverPresenter.h"
#include "use_case/GamePlay.h"
#include "use_case/GameStorage.h"
#include "use_case/ScorePresenter.h"
#include "use_case/Storage.h"

namespace use_case {

template <typename Board, typename Score>
class Game : public GameStorage, public GamePlay {
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
    assert(boardPresenter && "Board presenter is null");
    board = Board{};
    boardPresenter->initWithDimension(board.getRows(), board.getCols());

    common::Actions actions;
    actions.newActions.emplace_back(newCell());
    actions.newActions.emplace_back(newCell());
    presentAll(actions);
  }

  void loadGame() override {
    assert(boardPresenter && "Board presenter is null");
    assert(storage && "Storage is null");
    const auto gameData = storage->loadGame();
    if (gameData.isGameOver) {
      newGame();
    } else {
      score = Score{gameData.score, gameData.bestScore};
      board = Board{gameData.rows, gameData.cols, gameData.newActions};
      boardPresenter->initWithDimension(board.getRows(), board.getCols());
      presentAll({
          {},
          {},
          std::move(gameData.newActions),
      });
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
    assert(storage && "Storage is null");
    storage->saveGame({score.getBestScore(), score.getScore(),
                       board.isGameOver(), board.getRows(), board.getCols(),
                       board.restoreActions()});
  }

 private:
  common::NewAction newCell() {
    const auto emptyPositions = board.emptyPositions();
    const auto pos = emptyPositions[random->next(0, emptyPositions.size() - 1)];
    const auto value = random->next(1, 10) == 1 ? 4 : 2;
    return board.addCell(pos, value);
  }

  void presentAll(common::Actions actions) {
    assert(boardPresenter && "Board presenter is null");
    boardPresenter->present(std::move(actions));
    assert(scorePresenter && "Score presenter is null");
    scorePresenter->present(score.getScore(), score.getBestScore());
    if (board.isGameOver()) {
      assert(gameOverPresenter && "Game over presenter is null");
      gameOverPresenter->present();
    }
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
