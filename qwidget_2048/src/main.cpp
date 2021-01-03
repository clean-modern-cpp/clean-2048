#include <QApplication>
#include <QTime>

#include "MainWindow.h"
#include "storage/Storage.h"
#include "use_case/Storage.h"

int main(int argc, char *argv[]) {
  use_case::setStorage(std::make_unique<storage::Storage>());

  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}
