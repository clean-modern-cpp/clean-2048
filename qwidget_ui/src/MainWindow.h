#ifndef CLEAN2048_QWIDGETUI_MAINWINDOW_H_
#define CLEAN2048_QWIDGETUI_MAINWINDOW_H_

#include <QWidget>

#include "qt_view_model/ScoreViewModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void scoreChanged(int score);
  void bestScoreChanged(int bestScore);

 private:
  void onScoreInc(int);
  void onGameOver();
  void onWin();

  Ui::MainWindow *ui;
  qt_view_model::ScoreViewModel scoreViewModel;
};

#endif
