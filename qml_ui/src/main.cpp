#include <QApplication>
#include <QQmlApplicationEngine>

#include "qt_view_model/BoardViewModel.h"

int main(int argc, char *argv[]) {
  qmlRegisterType<qt_view_model::BoardViewModel>("BoardViewModel", 1, 0,
                                                 "BoardViewModel");

  QApplication app(argc, argv);
  app.setApplicationName("2048");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

  return app.exec();
}
