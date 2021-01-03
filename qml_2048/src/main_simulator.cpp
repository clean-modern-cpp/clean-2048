#include <QApplication>
#include <QQmlApplicationEngine>
#include <vector>

#include "presenter/Router.h"
#include "qt_view_model/BoardViewModel.h"
#include "qt_view_model/Controller.h"
#include "qt_view_model/GameOverViewModel.h"
#include "qt_view_model/ScoreViewModel.h"
#include "use_case_interface/BoardPresenter.h"
#include "use_case_interface/GameOverPresenter.h"
#include "use_case_interface/GamePlay.h"
#include "use_case_interface/GameStorage.h"
#include "use_case_interface/ScorePresenter.h"

class UseCaseMockup : public use_case_interface::GamePlay,
                      public use_case_interface::GameStorage {
 public:
  void newGame() override {}
  void loadGame() override { boardPresenter->initWithDimension(4, 4); }
  void saveGame() override {}
  void swipe(common::Direction) override {
    if (index < actionsArray.size()) {
      boardPresenter->present(actionsArray[index++]);
    }
  }

  void setBoardPresenter(use_case_interface::BoardPresenter* presenter) {
    boardPresenter = presenter;
  }

  void setScorePresenter(use_case_interface::ScorePresenter* presenter) {
    scorePresenter = presenter;
  }

  void setGameOverPresenter(use_case_interface::GameOverPresenter* presenter) {
    gameOverPresenter = presenter;
  }

 private:
  use_case_interface::BoardPresenter* boardPresenter;
  use_case_interface::ScorePresenter* scorePresenter;
  use_case_interface::GameOverPresenter* gameOverPresenter;

  std::size_t index = 0;
  inline static const std::vector<common::Actions> actionsArray{
      {
          {},
          {},
          {
              {{1, 1}, 2},
          },
      },
      {
          {
              {{1, 1}, {1, 3}},
          },
          {},
          {
              {{1, 0}, 2},
              {{2, 2}, 4},
          },
      },
      {
          {
              {{1, 0}, {0, 0}},
              {{2, 2}, {0, 2}},
          },
          {
              {{0, 0}, 16},
          },
          {
              {{3, 3}, 8},
          },
      },
      {
          {
              {{0, 2}, {0, 1}},
              {{1, 3}, {1, 0}},
              {{3, 3}, {3, 0}},
          },
          {
              {{0, 0}, 256},
          },
          {
              {{2, 2}, 2},
          },
      },
      {
          {
              {{0, 1}, {3, 1}},
              {{2, 2}, {3, 2}},
          },
          {
              {{1, 0}, 2048},
          },
          {},
      },
  };
};

class RouterMockup : public presenter::Router {
 public:
  use_case_interface::GamePlay* getGamePlay() override { return &useCase; }

  use_case_interface::GameStorage* getGameStorage() override {
    return &useCase;
  }

  void setBoardPresenter(
      use_case_interface::BoardPresenter* presenter) override {
    useCase.setBoardPresenter(presenter);
  }

  void setScorePresenter(
      use_case_interface::ScorePresenter* presenter) override {
    useCase.setScorePresenter(presenter);
  }

  void setGameOverPresenter(
      use_case_interface::GameOverPresenter* presenter) override {
    useCase.setGameOverPresenter(presenter);
  }

 private:
  UseCaseMockup useCase;
};

int main(int argc, char* argv[]) {
  presenter::setRouter(std::make_unique<RouterMockup>());

  qmlRegisterType<qt_view_model::Controller>("Clean_2048.Controller", 1, 0,
                                             "Controller");
  qmlRegisterType<qt_view_model::BoardViewModel>("Clean_2048.BoardViewModel", 1,
                                                 0, "BoardViewModel");
  qmlRegisterType<qt_view_model::ScoreViewModel>("Clean_2048.ScoreViewModel", 1,
                                                 0, "ScoreViewModel");
  qmlRegisterType<qt_view_model::GameOverViewModel>(
      "Clean_2048.GameOverViewModel", 1, 0, "GameOverViewModel");

  QApplication app(argc, argv);
  app.setApplicationName("2048");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:///qml/Main.qml")));

  return app.exec();
}
