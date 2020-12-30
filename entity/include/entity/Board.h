#ifndef CLEAN2048_ENTITY_BOARD_H_
#define CLEAN2048_ENTITY_BOARD_H_

#include <memory>

#include "common/Model.h"

namespace entity {

class Board {
 public:
  Board(common::Index rows, common::Index cols);
  ~Board();

  common::Index getRows() const;
  common::Index getCols() const;

  void clear();

  common::Positions emptyPositions() const;

  common::NewAction addCell(common::Position pos, common::Value value);
  common::SwipeAction swipe(common::Direction direction);

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace entity

#endif
