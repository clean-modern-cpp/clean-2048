#include "BoardView.h"

#include <QKeyEvent>
#include <QLabel>
#include <QPropertyAnimation>

#include "CellView.h"

BoardView::BoardView(QWidget *parent) : QWidget(parent) {
  connect(&boardViewModel, SIGNAL(newCell(int, int, QString)), this,
          SLOT(newCell(int, int, QString)));
  connect(&boardViewModel, SIGNAL(startCellMove(int, int, int, int)), this,
          SLOT(startCellMove(int, int, int, int)));
  connect(&boardViewModel, SIGNAL(completeCellMove(int, int, int, int)), this,
          SLOT(completeCellMove(int, int, int, int)));
  connect(&boardViewModel, SIGNAL(changeCell(int, int, QString)), this,
          SLOT(changeCell(int, int, QString)));

  cells = std::vector<std::vector<CellView *>>(
      4, std::vector<CellView *>(4, nullptr));
  boardViewModel.restart();
}

void BoardView::keyPressEvent(QKeyEvent *event) {
  boardViewModel.swipe(event->key());
  QWidget::keyPressEvent(event);
}

void BoardView::newCell(int row, int col, QString value) {
  auto cell = new CellView(this);
  cell->resize(width() / 4, height() / 4);
  cell->setText(value);
  cell->show();
  cells[row][col] = cell;
  auto animation = new QPropertyAnimation{cell, "geometry"};
  animation->setDuration(100);
  animation->setStartValue(QRect{cell->width() * col + cell->width() / 2,
                                 cell->height() * row + cell->height() / 2, 0,
                                 0});
  animation->setEndValue(QRect{cell->width() * col, cell->height() * row,
                               cell->width(), cell->height()});
  animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void BoardView::startCellMove(int fromRow, int fromCol, int toRow, int toCol) {
  auto cell = cells[fromRow][fromCol];
  Q_ASSERT(cell != nullptr);
  auto animation = new QPropertyAnimation{cell, "pos"};
  animation->setDuration(100);
  animation->setStartValue(
      QPoint{cell->width() * fromCol, cell->height() * fromRow});
  animation->setEndValue(QPoint{cell->width() * toCol, cell->height() * toRow});
  animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void BoardView::completeCellMove(int fromRow, int fromCol, int toRow,
                                 int toCol) {
  if (cells[toRow][toCol]) {
    delete cells[toRow][toCol];
  }
  cells[toRow][toCol] = cells[fromRow][fromCol];
  cells[fromRow][fromCol] = nullptr;
}

void BoardView::changeCell(int row, int col, QString value) {
  auto cell = cells[row][col];
  Q_ASSERT(cell != nullptr);
  cell->setText(value);
  cell->update();
}
