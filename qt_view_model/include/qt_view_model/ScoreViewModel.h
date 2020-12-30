#ifndef CLEAN2048_QTVIEWMODEL_SCOREVIEWMODEL_H_
#define CLEAN2048_QTVIEWMODEL_SCOREVIEWMODEL_H_

#include <spdlog/spdlog.h>

#include <QObject>

#include "presenter/ScorePresenter.h"

namespace qt_view_model {

class ScoreViewModel : public QObject, presenter::ScorePresenterDelegate {
  Q_OBJECT

 public:
  Q_PROPERTY(int score MEMBER score NOTIFY scoreChanged)
  Q_PROPERTY(int bestScore MEMBER bestScore NOTIFY bestScoreChanged)

  explicit ScoreViewModel(QObject* parent = nullptr);

  void present(int s, int bs) override {
    spdlog::info("present score: {}, {}", score, bestScore);
    score = s;
    bestScore = bs;
    emit scoreChanged();
    emit bestScoreChanged();
  }

 signals:
  void scoreChanged();
  void bestScoreChanged();

 private:
  presenter::ScorePresenter scorePresenter;
  int score = 0;
  int bestScore = 0;
};

}  // namespace qt_view_model

#endif
