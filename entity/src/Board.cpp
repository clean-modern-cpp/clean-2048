#include "entity/Board.h"

#include <algorithm>
#include <cassert>

namespace entity {

template <Index Size>
constexpr auto totalSizeOfMatrix = Size* Size;

struct BaseDirectionTraits {
  explicit BaseDirectionTraits(Index begin, Index end, Index offset)
      : begin{begin}, end{end}, offset{offset} {}
  const Index begin;
  const Index end;
  const Index offset;
};

template <Direction D, Index Size>
struct DirectionTraits {};

template <Index Size>
struct DirectionTraits<Direction::left, Size> : BaseDirectionTraits {
  explicit DirectionTraits(Index line)
      : BaseDirectionTraits{line * Size, line * Size + Size, 1} {}
};

template <int Size>
struct DirectionTraits<Direction::right, Size> : BaseDirectionTraits {
  explicit DirectionTraits(Index line)
      : BaseDirectionTraits{(line + 1) * Size - 1, line * Size - 1, -1} {}
};

template <int Size>
struct DirectionTraits<Direction::up, Size> : BaseDirectionTraits {
  explicit DirectionTraits(Index line)
      : BaseDirectionTraits{line, totalSizeOfMatrix<Size>, Size} {}
};

template <int Size>
struct DirectionTraits<Direction::down, Size> : BaseDirectionTraits {
  explicit DirectionTraits(Index line)
      : BaseDirectionTraits{totalSizeOfMatrix<Size> - line - 1, -1, -Size} {}
};

template <Direction D, int Size>
inline static Index next(Index index, const DirectionTraits<D, Size>& dt) {
  return index + dt.offset;
}

template <Direction D, int Size>
inline static bool isInLine(Index index, const DirectionTraits<D, Size>& dt) {
  return dt.offset > 0 ? index < dt.end : index > dt.end;
}

class Board::Impl {
 public:
  Impl() : values(totalSizeOfMatrix<Size>, empty) {}

  Positions emptyPositions() const {
    Positions positions;
    for (auto index = 0; index < totalSizeOfMatrix<Size>; ++index) {
      if (values[index] == empty) {
        positions.push_back(positionOf(index));
      }
    }
    return positions;
  }

  NewAction addCell(Position pos, Value value) {
    assert(pos.row >= 0 && pos.row < Size);
    assert(pos.column >= 0 && pos.column < Size);
    assert(values[indexOf(pos)] == empty);
    values[indexOf(pos)] = value;
    return {pos, value};
  }

  SwipeAction swipe(Direction direction) {
    SwipeAction action;
    for (auto line = 0; line < Size; ++line) {
      switch (direction) {
        case Direction::left:
          moveLine<Direction::left>(line, action);
          break;
        case Direction::right:
          moveLine<Direction::right>(line, action);
          break;
        case Direction::up:
          moveLine<Direction::up>(line, action);
          break;
        case Direction::down:
          moveLine<Direction::down>(line, action);
          break;
      }
    }
    return action;
  }

 private:
  static Index indexOf(Position pos) { return pos.row * Size + pos.column; }
  static Position positionOf(Index index) {
    return {index / Size, index % Size};
  }

  template <Direction direction>
  void moveLine(Index line, SwipeAction& action) {
    const DirectionTraits<direction, Size> dt{line};
    Index dest = dt.begin;
    Index src = next(dest, dt);
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
          const Value from = values[dest];
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

  constexpr static Value empty = 0;
  constexpr static Index Size = 4;

  std::vector<Value> values;
};

Board::Board() : impl{std::make_unique<Impl>()} {}

Board::~Board() {}

Positions Board::emptyPositions() const { return impl->emptyPositions(); }

NewAction Board::addCell(Position pos, Value value) {
  return impl->addCell(pos, value);
}

SwipeAction Board::swipe(Direction direction) { return impl->swipe(direction); }

}  // namespace entity
