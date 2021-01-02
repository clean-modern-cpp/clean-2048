#ifndef CLEAN2048_QTVIEWMODEL_CONTROLLER_H_
#define CLEAN2048_QTVIEWMODEL_CONTROLLER_H_

#include <QObject>

#include "presenter/Controller.h"

namespace qt_view_model {

class Controller : public QObject {
  Q_OBJECT

 public:
  explicit Controller(QObject* parent = nullptr);

  Q_INVOKABLE void newGame() { controller.newGame(); }

  Q_INVOKABLE void loadGame() { controller.loadGame(); }

  Q_INVOKABLE void saveGame() { controller.saveGame(); }

 private:
  presenter::Controller controller;
};

}  // namespace qt_view_model

#endif
