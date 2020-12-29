#include "MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->boardView->setFocus();

  highScore = 0;
  QFile file("score.j");
  if (file.open(QIODevice::ReadOnly)) {
    file.read((char *)&highScore, sizeof(highScore));
    file.close();
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onScoreInc(int) {}

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
