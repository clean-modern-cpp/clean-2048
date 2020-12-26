#ifndef CLEAN2048_QWIDGETUI_MAINWINDOW_H_
#define CLEAN2048_QWIDGETUI_MAINWINDOW_H_

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class BoardView;
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
