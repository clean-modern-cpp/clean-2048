#include "MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint), bPressFlag(false) {
  setAutoFillBackground(true);
  QPalette pal = palette();
  pal.setColor(QPalette::Window, QColor("#FAF8F0"));
  setPalette(pal);

  titleLabel = new QLabel(tr("2048"), this);
  titleLabel->setStyleSheet("color:#746D65;");
  titleLabel->setFont(QFont("arial", 45, QFont::Black));

  tipsLabel =
      new QLabel(tr("Join the numbers and get to the 2048 tile!"), this);
  tipsLabel->setStyleSheet("color:#B3AFA7;");
  tipsLabel->setFont(QFont("arial", 10, QFont::Normal));
  highScore = 0;
  QFile file("score.j");
  if (file.open(QIODevice::ReadOnly)) {
    file.read((char *)&highScore, sizeof(highScore));
    file.close();
  }

  gameView = new GameView(this);
  gameView->setFocus();
  connect(gameView, SIGNAL(ScoreInc(int)), this, SLOT(onScoreInc(int)));
  connect(gameView, SIGNAL(GameOver()), this, SLOT(onGameOver()));
  connect(gameView, SIGNAL(win()), this, SLOT(onWin()));

  QFont font;
  font.setFamily("Arial");
  font.setBold(true);
  font.setPixelSize(15);

  restartBtn = new QPushButton("New Game", this);
  restartBtn->setFont(font);
  restartBtn->setStyleSheet(
      "QPushButton{color: white;background:#907963;border-style:flat;}");
  restartBtn->setFocusPolicy(Qt::NoFocus);
  connect(restartBtn, SIGNAL(clicked()), gameView, SLOT(restart()));

  highScoreLbl = new QLabel(QString("BEST\n%1").arg(highScore), this);
  highScoreLbl->setFont(font);
  highScoreLbl->setAlignment(Qt::AlignCenter);
  highScoreLbl->setStyleSheet("QLabel{color:#FFFFEE;background:#BEAD9D}");

  scoreLbl = new QLabel("SCORE\n0", this);
  scoreLbl->setFont(font);
  scoreLbl->setAlignment(Qt::AlignCenter);
  scoreLbl->setStyleSheet("QLabel{color:#FFFFEE;background:#BEAD9D}");

  closeBtn = new QPushButton("x", this);
  closeBtn->setFocusPolicy(Qt::NoFocus);
  closeBtn->setFont(QFont("Arial", 11, QFont::Normal));

  closeBtn->setStyleSheet(
      "QPushButton{border-style:flat;color:#BDAD9F}"
      "QPushButton:hover{border-style:flat;color:#FF0000}");
  closeBtn->setCursor(Qt::PointingHandCursor);
  closeBtn->setGeometry(400 - 18, 3, 15, 15);
  connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

  resize(400, 510);
}

MainWindow::~MainWindow() {
  delete restartBtn;
  delete scoreLbl;
  delete highScoreLbl;
  delete gameView;
}

void MainWindow::onScoreInc(int score) {
  scoreLbl->setText(QString("Score:\n %1").arg(score));
  if (score > highScore) {
    highScore = score;
    highScoreLbl->setText(QString("BEST:\n %1").arg(highScore));
    QFile file("score.j");
    file.open(QIODevice::WriteOnly);
    file.write((char *)&highScore, sizeof(highScore));
    file.close();
  }
}

void MainWindow::onGameOver() {
  QMessageBox::information(this, "GameOver", "You lost !");
}

void MainWindow::onWin() {
  QMessageBox::information(this, "Congratulation", "You win !");
}

void MainWindow::resizeEvent(QResizeEvent *) {
  ratioW = width() / 400.0f;
  ratioH = height() / 510.0f;
  titleLabel->setGeometry(20 * ratioW, 40 * ratioH, 130 * ratioW, 50 * ratioH);
  tipsLabel->setGeometry(20 * ratioW, 100 * ratioH, 300 * ratioW, 20 * ratioH);
  gameView->setGeometry(18 * ratioW, 140 * ratioH, 365 * ratioW, 365 * ratioH);
  restartBtn->setGeometry(280 * ratioW, 90 * ratioH, 100 * ratioW, 30 * ratioH);
  highScoreLbl->setGeometry(300 * ratioW, 40 * ratioH, 80 * ratioW,
                            40 * ratioH);
  scoreLbl->setGeometry(210 * ratioW, 40 * ratioH, 80 * ratioW, 40 * ratioH);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  gameView->setFocus();
  QWidget::keyPressEvent(event);
}
void MainWindow::mousePressEvent(QMouseEvent *event) {
  bPressFlag = true;
  dragPosition = event->pos();
  QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (bPressFlag) {
    QPoint relaPos(QCursor::pos() - dragPosition);
    move(relaPos);
  }
  QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  bPressFlag = false;
  QWidget::mouseReleaseEvent(event);
}
