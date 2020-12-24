#ifndef CLEAN_2048_QML_UI_BOARDVIEWMODEL_H
#define CLEAN_2048_QML_UI_BOARDVIEWMODEL_H

#include <QObject>
#include <QString>
#include <vector>

struct Position {
  int row = 0;
  int column = 0;
};

struct MovePosition {
  MovePosition() {}
  MovePosition(Position from, Position to) : from{from}, to{to} {}

  Position from;
  Position to;
};

using MovePositions = std::vector<MovePosition>;

class BoardViewModel : public QObject {
  Q_OBJECT

  Q_PROPERTY(int rows MEMBER rows NOTIFY rowsChanged)
  Q_PROPERTY(int columns MEMBER columns NOTIFY columnChanged)

 public:
  explicit BoardViewModel(QObject* parent = nullptr);

  Q_INVOKABLE int movePositionLength() const { return movePositions.size(); }
  Q_INVOKABLE int fromRow(int index) const {
    return movePositions[index].from.row;
  }
  Q_INVOKABLE int fromColumn(int index) const {
    return movePositions[index].from.column;
  }
  Q_INVOKABLE int toRow(int index) const { return movePositions[index].to.row; }
  Q_INVOKABLE int toColumn(int index) const {
    return movePositions[index].to.column;
  }

  Q_INVOKABLE int numberOf(int row, int column) const {
    return numbers[row][column];
  }

  Q_INVOKABLE void restart() {
    for (auto row : numbers) {
      for (auto& n : row) {
        n = 0;
      }
    }
    rndBlock();
    rndBlock();
  }

  Q_INVOKABLE void rndBlock() {
    std::vector<Position> emptyPositions;
    for (auto row = 0; row < rows; row++) {
      for (auto column = 0; column < columns; column++) {
        if (numbers[row][column] == 0) {
          emptyPositions.push_back({row, column});
        }
      }
    }
    if (!emptyPositions.empty()) {
      const int index = std::rand() % emptyPositions.size();
      const int value = std::rand() < RAND_MAX * 0.5 ? 2 : 4;
      numbers[emptyPositions[index].row][emptyPositions[index].column] = value;
    } else {
    }
  }

  Q_INVOKABLE bool moveLeftUp(bool left) {
    movePositions.clear();
    for (auto row = 0; row < rows; ++row) {
      for (auto column = 0; column < columns; ++column) {
        for (auto f = column + 1; f < rows; ++f) {
          if (left) {
            if (!moveObj(row, f, row, column)) break;
          } else {
            if (!moveObj(f, row, column, row)) break;
          }
        }
      }
    }
    return true;
  }

  Q_INVOKABLE bool moveRightDown(bool right) {
    movePositions.clear();
    for (auto row = 0; row < rows; ++row) {
      for (auto column = columns - 1; column >= 0; --column) {
        for (auto f = column - 1; f >= 0; --f) {
          if (right) {
            if (!moveObj(row, f, row, column)) break;
          } else {
            if (!moveObj(f, row, column, row)) break;
          }
        }
      }
    }
    return true;
  }

  bool moveObj(int row, int col, int row2, int col2) {
    const auto cell1 = numbers[row][col];
    const auto cell2 = numbers[row2][col2];
    if (cell1 != 0 && cell2 != 0 && cell1 != cell2) return false;
    if ((cell1 != 0 && cell1 == cell2) || (cell1 != 0 && cell2 == 0)) {
      numbers[row][col] = 0;
      movePositions.emplace_back(Position{row, col}, Position{row2, col2});
    }
    if (cell1 != 0 && cell1 == cell2) {
      numbers[row2][col2] *= 2;
      return false;
    }
    if (cell1 != 0 && cell2 == 0) {
      numbers[row2][col2] = cell1;
      return true;
    }
    return true;
  }

 signals:
  void rowsChanged();
  void columnChanged();

 private:
  int rows = 4;
  int columns = 4;

  MovePositions movePositions;
  std::vector<std::vector<int>> numbers;
};

#endif
