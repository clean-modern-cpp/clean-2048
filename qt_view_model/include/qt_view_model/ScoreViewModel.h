#ifndef CLEAN2048_QTVIEWMODEL_SCOREVIEWMODEL_H_
#define CLEAN2048_QTVIEWMODEL_SCOREVIEWMODEL_H_

#include <spdlog/spdlog.h>

#include <QObject>

#include "presenter/ScorePresenter.h"

namespace qt_view_model {

class ScoreViewModel : public QObject, presenter::ScorePresenterDelegate {
  Q_OBJECT

 public:
  Q_PROPERTY(int score MEMBER scoreCache NOTIFY scoreChanged)
  Q_PROPERTY(int bestScore MEMBER bestScoreCache NOTIFY bestScoreChanged)

  explicit ScoreViewModel(QObject* parent = nullptr);

  void present(int score, int bestScore) override {
    spdlog::info("present score: {}, {}", score, bestScore);
    scoreCache = score;
    bestScoreCache = bestScore;
    emit scoreChanged(score);
    emit bestScoreChanged(bestScore);
  }

 signals:
  void scoreChanged(int score);
  void bestScoreChanged(int bestScore);

 private:
  presenter::ScorePresenter scorePresenter;

  int scoreCache = 0;
  int bestScoreCache = 0;
};

}  // namespace qt_view_model

#endif
