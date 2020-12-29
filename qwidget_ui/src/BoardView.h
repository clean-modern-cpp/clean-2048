#ifndef CLEAN2048_QWIDGETUI_BOARDVIEW_H_
#define CLEAN2048_QWIDGETUI_BOARDVIEW_H_

#include <QString>
#include <QWidget>
#include <vector>

#include "CellView.h"
#include "qt_view_model/BoardViewModel.h"

class BoardView : public QWidget {
  Q_OBJECT

 public:
  explicit BoardView(QWidget *parent = 0);

 private slots:
  void newCell(int row, int col, QString value);
  void startCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void completeCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void changeCell(int row, int col, QString value);

 private:
  void keyPressEvent(QKeyEvent *event);

  std::vector<std::vector<CellView *>> cells;

  qt_view_model::BoardViewModel boardViewModel;
};

#endif
