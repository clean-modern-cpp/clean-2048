#ifndef CLEAN2048_QWIDGETUI_BOARDVIEW_H_
#define CLEAN2048_QWIDGETUI_BOARDVIEW_H_

#include <QWidget>

enum GestureDirect { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

enum AnimationType { MOVE = 0, APPEARANCE = 1 };

struct Animation {
  AnimationType type;
  GestureDirect direct;
  QPointF startPos;
  QPointF endPos;
  int digit;
  int digit2;
};

class BoardView : public QWidget {
  Q_OBJECT

 public:
  explicit BoardView(QWidget *parent = 0);

 protected:
  void keyPressEvent(QKeyEvent *event);

 private:
  int board[4][4];
  int digitCount;
  int score;
  QPoint startPos;
  QList<Animation> animationList;
  qreal w, h;
  QImage *cacheImg;
  bool isAnimating;
  bool checkGameOver();
  bool checkWin();
  int getBitCount(int);
  bool playAnimation(Animation &, QPainter &);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void paintEvent(QPaintEvent *);

 signals:
  void GestureMove(GestureDirect);
  void ScoreInc(int);
  void GameOver();
  void win();

 public slots:
  void onGestureMove(GestureDirect);
  void restart();
};

#endif
