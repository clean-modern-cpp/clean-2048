#ifndef CLEAN2048_CONSOLEUI_BOARDVIEW_H_
#define CLEAN2048_CONSOLEUI_BOARDVIEW_H_

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <vector>

#include "common/Model.h"
#include "common/ModelHelper.h"
#include "presenter/BoardPresenter.h"

namespace console_ui {

class BoardView : public presenter::BoardPresenterDelegate {
 public:
  std::string body() {
    const std::string seperator = "---------------------------------\n";
    std::string body;
    do {
      performAction();
      for (const auto& row : board) {
        body += seperator + "| ";
        for (const auto value : row) {
          std::ostringstream oss;
          oss << std::setw(5) << value;
          body += (value != 0 ? oss.str() : "     ") + " | ";
        }
        body += "\n";
      }
      body += seperator + "\n";
    } while (!actions.moveActions.empty());
    return body;
  }

  void intiWithDimension(int row, int column) override {
    board = Board(row, Row(column, emptyTile));
  }

  void present(common::Actions acts) override { actions = std::move(acts); }

 private:
  void performAction() {
    if (!moveCells()) {
      actions.moveActions.clear();
      newCells();
      mergeCells();
    }
  }

  bool moveCells() {
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

  void newCells() {
    for (const auto& action : actions.newActions) {
      assert(cellAt(action.pos) == emptyTile);
      cellAt(action.pos) = action.value;
    }
    actions.newActions.clear();
  }

  void mergeCells() {
    for (const auto& action : actions.mergeActions) {
      assert(cellAt(action.pos) != emptyTile);
      cellAt(action.pos) = action.toValue;
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
