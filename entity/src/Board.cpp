#include "entity/Board.h"

#include <algorithm>
#include <cassert>
#include <vector>

namespace entity {

template <common::Index Size>
constexpr auto totalSizeOfMatrix = Size* Size;

struct BaseDirectionTraits {
  explicit BaseDirectionTraits(common::Index begin, common::Index end,
                               common::Index offset)
      : begin{begin}, end{end}, offset{offset} {}
  const common::Index begin;
  const common::Index end;
  const common::Index offset;
};

template <common::Direction D, common::Index Size>
struct DirectionTraits {};

template <common::Index Size>
struct DirectionTraits<common::Direction::left, Size> : BaseDirectionTraits {
  explicit DirectionTraits(common::Index line)
      : BaseDirectionTraits{line * Size, line * Size + Size, 1} {}
};

template <common::Index Size>
struct DirectionTraits<common::Direction::right, Size> : BaseDirectionTraits {
  explicit DirectionTraits(common::Index line)
      : BaseDirectionTraits{(line + 1) * Size - 1, line * Size - 1, -1} {}
};

template <int Size>
struct DirectionTraits<common::Direction::up, Size> : BaseDirectionTraits {
  explicit DirectionTraits(common::Index line)
      : BaseDirectionTraits{line, totalSizeOfMatrix<Size>, Size} {}
};

template <int Size>
struct DirectionTraits<common::Direction::down, Size> : BaseDirectionTraits {
  explicit DirectionTraits(common::Index line)
      : BaseDirectionTraits{totalSizeOfMatrix<Size> - line - 1, -1, -Size} {}
};

template <common::Direction D, int Size>
inline static common::Index next(common::Index index,
                                 const DirectionTraits<D, Size>& dt) {
  return index + dt.offset;
}

template <common::Direction D, int Size>
inline static bool isInLine(common::Index index,
                            const DirectionTraits<D, Size>& dt) {
  return dt.offset > 0 ? index < dt.end : index > dt.end;
}

class Board::Impl {
 public:
  Impl() : values(totalSizeOfMatrix<Size>, empty) {}

  common::Positions emptyPositions() const {
    common::Positions positions;
    for (auto index = 0; index < totalSizeOfMatrix<Size>; ++index) {
      if (values[index] == empty) {
        positions.push_back(positionOf(index));
      }
    }
    return positions;
  }

  void clear() {
    values = std::vector<common::Value>(totalSizeOfMatrix<Size>, empty);
  }

  common::NewAction addCell(common::Position pos, common::Value value) {
    assert(pos.row >= 0 && pos.row < Size);
    assert(pos.col >= 0 && pos.col < Size);
    assert(values[indexOf(pos)] == empty);
    values[indexOf(pos)] = value;
    return {pos, value};
  }

  common::SwipeAction swipe(common::Direction direction) {
    common::SwipeAction action;
    for (auto line = 0; line < Size; ++line) {
      switch (direction) {
        case common::Direction::left:
          moveLine<common::Direction::left>(line, action);
          break;
        case common::Direction::right:
          moveLine<common::Direction::right>(line, action);
          break;
        case common::Direction::up:
          moveLine<common::Direction::up>(line, action);
          break;
        case common::Direction::down:
          moveLine<common::Direction::down>(line, action);
          break;
      }
    }
    return action;
  }

 private:
  static common::Index indexOf(common::Position pos) {
    return pos.row * Size + pos.col;
  }
  static common::Position positionOf(common::Index index) {
    return {index / Size, index % Size};
  }

  template <common::Direction direction>
  void moveLine(common::Index line, common::SwipeAction& action) {
    const DirectionTraits<direction, Size> dt{line};
    common::Index dest = dt.begin;
    common::Index src = next(dest, dt);
    while (isInLine(dest, dt) && isInLine(src, dt)) {
      while (isInLine(src, dt) && values[src] == empty) {
        src = next(src, dt);
      }
      if (isInLine(src, dt)) {
        if (values[dest] == empty) {
          std::swap(values[dest], values[src]);
          action.moveActions.emplace_back(positionOf(src), positionOf(dest));
        } else if (values[dest] != values[src]) {
          dest = next(dest, dt);
          std::swap(values[dest], values[src]);
          action.moveActions.emplace_back(positionOf(src), positionOf(dest));
        } else {
          const auto from = values[dest];
          values[dest] = from * 2;
          values[src] = empty;
          action.moveActions.emplace_back(positionOf(src), positionOf(dest));
          action.changeActions.emplace_back(positionOf(dest), from,
                                            values[dest]);
          dest = next(dest, dt);
        }
        src = next(src, dt);
      }
    }
  }

  constexpr static common::Value empty = 0;
  constexpr static common::Index Size = 4;

  std::vector<common::Value> values;
};

Board::Board() : impl{std::make_unique<Impl>()} {}

Board::~Board() {}

common::Positions Board::emptyPositions() const {
  return impl->emptyPositions();
}

void Board::clear() { impl->clear(); }

common::NewAction Board::addCell(common::Position pos, common::Value value) {
  return impl->addCell(pos, value);
}

common::SwipeAction Board::swipe(common::Direction direction) {
  return impl->swipe(direction);
}

}  // namespace entity
