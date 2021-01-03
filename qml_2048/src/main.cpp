#include <QApplication>
#include <QQmlApplicationEngine>

#include "qt_view_model/BoardViewModel.h"
#include "qt_view_model/Controller.h"
#include "qt_view_model/GameOverViewModel.h"
#include "qt_view_model/ScoreViewModel.h"
#include "router/Router.h"
#include "storage/Storage.h"

int main(int argc, char *argv[]) {
  presenter::setRouter(std::make_unique<router::Router>());
  use_case::setStorage(std::make_unique<storage::Storage>());

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
