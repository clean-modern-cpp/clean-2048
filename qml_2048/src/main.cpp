#include <QApplication>
#include <QQmlApplicationEngine>

#include "qt_view_model/BoardViewModel.h"
#include "qt_view_model/Controller.h"
#include "qt_view_model/GameOverViewModel.h"
#include "qt_view_model/ScoreViewModel.h"
#include "storage/Storage.h"
#include "use_case/Storage.h"

int main(int argc, char *argv[]) {
  use_case::setStorage(std::make_unique<storage::Storage>());

  qmlRegisterType<qt_view_model::Controller>("Controller", 1, 0, "Controller");
  qmlRegisterType<qt_view_model::BoardViewModel>("BoardViewModel", 1, 0,
                                                 "BoardViewModel");
  qmlRegisterType<qt_view_model::ScoreViewModel>("ScoreViewModel", 1, 0,
                                                 "ScoreViewModel");
  qmlRegisterType<qt_view_model::GameOverViewModel>("GameOverViewModel", 1, 0,
                                                    "GameOverViewModel");

  QApplication app(argc, argv);
  app.setApplicationName("2048");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:///qml/Main.qml")));

  return app.exec();
}
