#ifndef CLEAN2048_CONSOLEUI_BOARDVIEW_H_
#define CLEAN2048_CONSOLEUI_BOARDVIEW_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "common/Model.h"
#include "presenter/BoardPresenter.h"

namespace console_ui {

class BoardView : public presenter::BoardPresenterDelegate {
 public:
  bool isInAnimation() {
    return std::find_if(actions.moveActions.cbegin(),
                        actions.moveActions.cend(), [](const auto& moveAction) {
                          return moveAction.from != moveAction.to;
                        }) != actions.moveActions.cend();
  }

  std::string body();

  void intiWithDimension(int row, int column) override {
    board = Board(row, Row(column, emptyTile));
  }

  void present(common::Actions acts) override {
    std::cout << "board view present\n";
    actions = std::move(acts);
  }

 private:
  void performAction() {
    if (!moveTiles()) {
      actions.moveActions.clear();
      createTiles();
      doubleTiles();
    }
  }

  bool moveTiles() {
    bool moved = false;
    for (auto& moveAction : actions.moveActions) {
      if (moveAction.from != moveAction.to) {
        const auto next = moveTo(moveAction.from, moveAction.to);
        cellAt(next) = cellAt(moveAction.from);
        cellAt(moveAction.from) = emptyTile;
        moveAction.from = next;
        moved = true;
      }
    }
    return moved;
  }

  void createTiles() {
    for (auto& action : actions.newActions) {
      assert(cellAt(action.pos) == emptyTile);
      cellAt(action.pos) = action.value;
    }
    actions.newActions.clear();
  }

  void doubleTiles() {
    for (auto& action : actions.changeActions) {
      assert(cellAt(action.pos) != emptyTile);
      cellAt(action.pos) *= 2;
    }
  }

  int& cellAt(common::Position pos) { return board[pos.row][pos.col]; }

  common::Position moveTo(common::Position from, common::Position to) {
    return {from.row + diff(from.row, to.row),
            from.col + diff(from.col, to.col)};
  }

  static int diff(int from, int to) {
    return from != to ? (to - from) / std::abs(to - from) : 0;
  }

  constexpr static int emptyTile = 0;
  using Row = std::vector<int>;
  using Board = std::vector<Row>;

  common::Actions actions;
  Board board;
};

}  // namespace console_ui

#endif
