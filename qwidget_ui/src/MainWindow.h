#ifndef CLEAN2048_QWIDGETUI_MAINWINDOW_H_
#define CLEAN2048_QWIDGETUI_MAINWINDOW_H_

#include <QLabel>
#include <QPushButton>

#include "GameView.h"

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  QPushButton *restartBtn;
  QPushButton *closeBtn;
  QLabel *titleLabel;
  QLabel *tipsLabel;
  QLabel *scoreLbl;
  QLabel *highScoreLbl;
  GameView *gameView;
  qreal ratioW, ratioH;
  int highScore;
  QPoint dragPosition;
  bool bPressFlag;

 protected:
  void resizeEvent(QResizeEvent *);
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

 public slots:
  void onScoreInc(int);
  void onGameOver();
  void onWin();
};

#endif
