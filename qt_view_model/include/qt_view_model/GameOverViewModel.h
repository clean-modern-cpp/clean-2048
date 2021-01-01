#ifndef CLEAN2048_QTVIEWMODEL_GAMEOVERVIEWMODEL_H_
#define CLEAN2048_QTVIEWMODEL_GAMEOVERVIEWMODEL_H_

#include <spdlog/spdlog.h>

#include <QObject>

#include "presenter/GameOverPresenter.h"

namespace qt_view_model {

class GameOverViewModel : public QObject, presenter::GameOverPresenterDelegate {
  Q_OBJECT

 public:
  explicit GameOverViewModel(QObject* parent = nullptr);

  void present() override {
    spdlog::info("present game over");
    emit gameOver();
  }

 signals:
  void gameOver();

 private:
  presenter::GameOverPresenter gameOverPresenter;
};

}  // namespace qt_view_model

#endif
