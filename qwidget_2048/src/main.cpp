#include <QApplication>
#include <QTime>

#include "MainWindow.h"
#include "router/Router.h"
#include "storage/Storage.h"
#include "use_case/Storage.h"

int main(int argc, char *argv[]) {
  presenter::setRouter(std::make_unique<router::Router>());
  use_case::setStorage(std::make_unique<storage::Storage>());

  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
