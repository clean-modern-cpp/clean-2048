#ifndef CLEAN2048_ENTITY_BOARD_H_
#define CLEAN2048_ENTITY_BOARD_H_

#include <memory>

#include "common/Model.h"

namespace entity {

class Board {
 public:
  Board();
  Board(common::Index rows, common::Index cols, common::NewActions newActions);
  ~Board();

  Board(Board&&);
  Board& operator=(Board&&);

  common::Index getRows() const;
  common::Index getCols() const;

  common::Positions emptyPositions() const;
  bool isGameOver() const;

  void clear();
  common::NewAction addCell(common::Position pos, common::Value value);
  common::SwipeAction swipe(common::Direction direction);

  common::NewActions restoreActions() const;

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace entity

#endif
