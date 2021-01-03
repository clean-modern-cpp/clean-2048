#ifndef CLEAN2048_QWIDGETUI_MAINWINDOW_H_
#define CLEAN2048_QWIDGETUI_MAINWINDOW_H_

#include <QWidget>

#include "qt_view_model/Controller.h"
#include "qt_view_model/GameOverViewModel.h"
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
  void onScoreChanged(int score);
  void onBestScoreChanged(int bestScore);
  void onGameOver();

  void on_newGameButton_clicked();

 private:
  void closeEvent(QCloseEvent *bar);

  Ui::MainWindow *ui;

  qt_view_model::Controller controller;
  qt_view_model::GameOverViewModel gameOverViewModel;
  qt_view_model::ScoreViewModel scoreViewModel;
};

#endif
