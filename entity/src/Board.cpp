#include "entity/Board.h"

namespace entity {

template <int Size>
constexpr auto totalSizeOfMatrix = Size* Size;

template <int Size>
using Matrix = std::vector<int>;

struct BaseDirectionTraits {
  explicit BaseDirectionTraits(const int begin, const int end, const int offset)
      : begin{begin}, end{end}, offset{offset} {}
  const int begin;
  const int end;
  const int offset;
};

template <common::model::Direction D, int Size>
struct DirectionTraits {};

template <int Size>
struct DirectionTraits<common::model::Direction::left, Size>
    : BaseDirectionTraits {
  explicit DirectionTraits(int lineId)
      : BaseDirectionTraits{lineId * Size, lineId * Size + Size, 1} {}
};

template <int Size>
struct DirectionTraits<common::model::Direction::right, Size>
    : BaseDirectionTraits {
  explicit DirectionTraits(int lineId)
      : BaseDirectionTraits{(lineId + 1) * Size - 1, lineId * Size - 1, -1} {}
};

template <int Size>
struct DirectionTraits<common::model::Direction::up, Size>
    : BaseDirectionTraits {
  explicit DirectionTraits(int lineId)
      : BaseDirectionTraits{lineId, totalSizeOfMatrix<Size>, Size} {}
};

template <int Size>
struct DirectionTraits<common::model::Direction::down, Size>
    : BaseDirectionTraits {
  explicit DirectionTraits(int lineId)
      : BaseDirectionTraits{totalSizeOfMatrix<Size> - lineId - 1, -1, -Size} {}
};

template <common::model::Direction D, int Size>
inline static int next(int index, const DirectionTraits<D, Size>& dt) {
  return index + dt.offset;
}

template <common::model::Direction D, int Size>
inline static bool isInLine(int index, const DirectionTraits<D, Size>& dt) {
  return dt.offset > 0 ? index < dt.end : index > dt.end;
}

class Board::Impl {
 public:
  Impl() : numbers(totalSizeOfMatrix<Size>, empty) {}

  Tiles tiles() const {
    Tiles tiles;
    forEachTile([&](int row, int column, int number) {
      tiles.emplace_back(Position{row, column}, number);
    });
    return tiles;
  }

  void addTile(const Tile& tile) {
    assert(tile.pos.row >= 0 && tile.pos.row < Size);
    assert(tile.pos.column >= 0 && tile.pos.column < Size);
    assert(numbers[indexOf(tile.pos)] == empty);
    numbers[indexOf(tile.pos)] = tile.number;
  }

  void move(common::model::Direction direction) {
    for (auto lineId = 0; lineId < Size; ++lineId) {
      switch (direction) {
        case common::model::Direction::left:
          move<common::model::Direction::left>(lineId);
          break;
        case common::model::Direction::right:
          move<common::model::Direction::right>(lineId);
          break;
        case common::model::Direction::up:
          move<common::model::Direction::up>(lineId);
          break;
        case common::model::Direction::down:
          move<common::model::Direction::down>(lineId);
          break;
      }
    }
  }

 private:
  int rowOf(int index) const { return index / Size; }
  int columnOf(int index) const { return index % Size; }
  int indexOf(Position pos) const { return pos.row * Size + pos.column; }

  template <typename FUNC>
  void forEach(FUNC func) const {
    for (auto i = 0; i < static_cast<int>(numbers.size()); ++i) {
      func(rowOf(i), columnOf(i), numbers[i]);
    }
  }

  template <typename FUNC>
  void forEachTile(FUNC func) const {
    forEach([&](int row, int column, int number) {
      if (number != empty) {
        func(row, column, number);
      }
    });
  }

  template <typename FUNC>
  void forEachEmptyCell(FUNC func) const {
    forEach([&](int row, int column, int number) {
      if (number == empty) {
        func(row, column, number);
      }
    });
  }

  template <common::model::Direction direction>
  void move(int lineId) {
    const DirectionTraits<direction, Size> dt{lineId};
    int target = dt.begin;
    int src = next(target, dt);
    while (isInLine(target, dt) && isInLine(src, dt)) {
      while (isInLine(src, dt) && numbers[src] == empty) {
        src = next(src, dt);
      }
      if (isInLine(src, dt)) {
        if (numbers[target] == empty) {
          std::swap(numbers[target], numbers[src]);
        } else if (numbers[target] != numbers[src]) {
          target = next(target, dt);
          std::swap(numbers[target], numbers[src]);
        } else {
          numbers[target] *= 2;
          numbers[src] = empty;
          target = next(target, dt);
        }
        src = next(src, dt);
      }
    }
  }

  constexpr static int empty = 0;
  constexpr static int Size = 4;

  std::vector<int> numbers;
};

Board::Board() : impl{std::make_unique<Impl>()} {}

Board::~Board() {}

Tiles Board::tiles() const { return impl->tiles(); }

void Board::addTile(const Tile& tile) { return impl->addTile(tile); }

void Board::move(common::model::Direction direction) { impl->move(direction); }

}  // namespace entity
