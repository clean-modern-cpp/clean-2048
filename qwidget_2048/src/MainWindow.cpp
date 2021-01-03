#include "MainWindow.h"

#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->boardView->setFocus();

  connect(&gameOverViewModel, SIGNAL(gameOver()), this, SLOT(onGameOver()));
  connect(&scoreViewModel, SIGNAL(scoreChanged(int)), this,
          SLOT(onScoreChanged(int)));
  connect(&scoreViewModel, SIGNAL(bestScoreChanged(int)), this,
          SLOT(onBestScoreChanged(int)));
  controller.loadGame();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onScoreChanged(int score) {
  ui->score->setText(QString::number(score));
}

void MainWindow::onBestScoreChanged(int bestScore) {
  ui->bestScore->setText(QString::number(bestScore));
}

void MainWindow::on_newGameButton_clicked() { controller.newGame(); }

void MainWindow::onGameOver() {
  QMessageBox msgBox;
  msgBox.setText("Game Over");
  msgBox.setInformativeText("Try again!");
  msgBox.setDefaultButton(QMessageBox::Ok);
  msgBox.exec();
  controller.newGame();
}

void MainWindow::closeEvent(QCloseEvent *) { controller.saveGame(); }
