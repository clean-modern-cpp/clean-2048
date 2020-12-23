#ifndef CLEAN2048_ENTITY_BOARD_H_
#define CLEAN2048_ENTITY_BOARD_H_

#include <memory>
#include <vector>

#include "common/Model.h"

namespace entity {

struct Position {
  const int row;
  const int column;

  Position(const int row, const int column) : row{row}, column{column} {}

  friend bool operator==(const Position lhs, const Position rhs) {
    return lhs.row == rhs.row && lhs.column == rhs.column;
  }
};

struct Tile {
  const Position pos;
  const int number;

  Tile(const Position pos, const int number) : pos{pos}, number{number} {}

  friend bool operator==(const Tile &lhs, const Tile &rhs) {
    return lhs.pos == rhs.pos && lhs.number == rhs.number;
  }
};

using Tiles = std::vector<Tile>;

class Board {
 public:
  Board();
  ~Board();

  Tiles tiles() const;

  void addTile(const Tile &tile);

  void move(common::model::Direction direction);

 private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace entity

#endif
