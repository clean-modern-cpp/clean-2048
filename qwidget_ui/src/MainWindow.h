#ifndef CLEAN2048_QWIDGETUI_MAINWINDOW_H_
#define CLEAN2048_QWIDGETUI_MAINWINDOW_H_

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  int highScore;
  Ui::MainWindow *ui;

  void keyPressEvent(QKeyEvent *event);

  void onScoreInc(int);
  void onGameOver();
  void onWin();
};

#endif
