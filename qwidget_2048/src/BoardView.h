#ifndef CLEAN2048_QWIDGETUI_BOARDVIEW_H_
#define CLEAN2048_QWIDGETUI_BOARDVIEW_H_

#include <QString>
#include <QWidget>
#include <vector>

#include "CellView.h"
#include "qt_view_model/BoardViewModel.h"
#include "qt_view_model/Controller.h"

class BoardView : public QWidget {
  Q_OBJECT

 public:
  explicit BoardView(QWidget *parent = 0);

 private slots:
  void onInitWith(int rows, int cols);
  void onNewCell(int row, int col, QString value);
  void onStartCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void onCompleteCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void onMergeCell(int row, int col, QString value);

 private:
  void keyPressEvent(QKeyEvent *event);

  std::vector<std::vector<CellView *>> cells;

  qt_view_model::BoardViewModel boardViewModel;
  qt_view_model::Controller controller;
};

#endif
