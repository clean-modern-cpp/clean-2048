#include <QApplication>
#include <QQmlApplicationEngine>

#include "qt_view_model/BoardViewModel.h"
#include "qt_view_model/GameOverViewModel.h"
#include "qt_view_model/ScoreViewModel.h"

int main(int argc, char *argv[]) {
  qmlRegisterType<qt_view_model::BoardViewModel>("BoardViewModel", 1, 0,
                                                 "BoardViewModel");
  qmlRegisterType<qt_view_model::ScoreViewModel>("ScoreViewModel", 1, 0,
                                                 "ScoreViewModel");
  qmlRegisterType<qt_view_model::GameOverViewModel>("GameOverViewModel", 1, 0,
                                                    "GameOverViewModel");

  QApplication app(argc, argv);
  app.setApplicationName("2048");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

  return app.exec();
}
