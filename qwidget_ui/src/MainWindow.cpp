#include "MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->boardView->setFocus();

  connect(&scoreViewModel, SIGNAL(scoreChanged(int)), this,
          SLOT(scoreChanged(int)));
  connect(&scoreViewModel, SIGNAL(bestScoreChanged(int)), this,
          SLOT(bestScoreChanged(int)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::scoreChanged(int score) {
  ui->score->setText(QString::number(score));
}

void MainWindow::bestScoreChanged(int bestScore) {
  ui->bestScore->setText(QString::number(bestScore));
}

void MainWindow::onScoreInc(int) {}

void MainWindow::onGameOver() {
  QMessageBox::information(this, "GameOver", "You lost !");
}

void MainWindow::onWin() {
  QMessageBox::information(this, "Congratulation", "You win !");
}
