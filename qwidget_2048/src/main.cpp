#include <QApplication>

#include "MainWindow.h"
#include "router/Router.h"
#include "storage/Storage.h"

int main(int argc, char *argv[]) {
  presenter::setRouter(std::make_unique<router::Router>());
  use_case::setStorage(std::make_unique<storage::Storage>());

  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
