#include "MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // titleLabel = new QLabel(tr("2048"), this);
  // titleLabel->setStyleSheet("color:#746D65;");
  // titleLabel->setFont(QFont("arial", 45, QFont::Black));

  // tipsLabel =
  //     new QLabel(tr("Join the numbers and get to the 2048 tile!"), this);
  // tipsLabel->setStyleSheet("color:#B3AFA7;");
  // tipsLabel->setFont(QFont("arial", 10, QFont::Normal));

  highScore = 0;
  QFile file("score.j");
  if (file.open(QIODevice::ReadOnly)) {
    file.read((char *)&highScore, sizeof(highScore));
    file.close();
  }

  // boardView = new BoardView(this);
  // boardView->setFocus();
  // connect(boardView, SIGNAL(ScoreInc(int)), this, SLOT(onScoreInc(int)));
  // connect(boardView, SIGNAL(GameOver()), this, SLOT(onGameOver()));
  // connect(boardView, SIGNAL(win()), this, SLOT(onWin()));

  // QFont font;
  // font.setFamily("Arial");
  // font.setBold(true);
  // font.setPixelSize(15);

  // restartBtn = new QPushButton("New Game", this);
  // restartBtn->setFont(font);
  // restartBtn->setStyleSheet(
  //     "QPushButton{color: white;background:#907963;border-style:flat;}");
  // restartBtn->setFocusPolicy(Qt::NoFocus);
  // connect(restartBtn, SIGNAL(clicked()), boardView, SLOT(restart()));

  // highScoreLbl = new QLabel(QString("BEST\n%1").arg(highScore), this);
  // highScoreLbl->setFont(font);
  // highScoreLbl->setAlignment(Qt::AlignCenter);
  // highScoreLbl->setStyleSheet("QLabel{color:#FFFFEE;background:#BEAD9D}");

  // scoreLbl = new QLabel("SCORE\n0", this);
  // scoreLbl->setFont(font);
  // scoreLbl->setAlignment(Qt::AlignCenter);
  // scoreLbl->setStyleSheet("QLabel{color:#FFFFEE;background:#BEAD9D}");

  // resize(400, 510);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onScoreInc(int) {
  // scoreLbl->setText(QString("Score:\n %1").arg(score));
  // if (score > highScore) {
  //   highScore = score;
  //   highScoreLbl->setText(QString("BEST:\n %1").arg(highScore));
  //   QFile file("score.j");
  //   file.open(QIODevice::WriteOnly);
  //   file.write((char *)&highScore, sizeof(highScore));
  //   file.close();
  // }
}

void MainWindow::onGameOver() {
  QMessageBox::information(this, "GameOver", "You lost !");
}

void MainWindow::onWin() {
  QMessageBox::information(this, "Congratulation", "You win !");
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  ui->boardView->setFocus();
  QWidget::keyPressEvent(event);
}
