#ifndef CLEAN2048_QTVIEWMODEL_BOARDVIEWMODEL_H_
#define CLEAN2048_QTVIEWMODEL_BOARDVIEWMODEL_H_

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <QKeyEvent>
#include <QObject>
#include <QString>
#include <QTimer>
#include <unordered_map>
#include <vector>

#include "common/ModelHelper.h"
#include "presenter/BoardPresenter.h"
#include "presenter/Controller.h"

namespace qt_view_model {

class BoardViewModel : public QObject, presenter::BoardPresenterDelegate {
  Q_OBJECT

 public:
  Q_PROPERTY(int rows MEMBER rows NOTIFY rowsChanged)
  Q_PROPERTY(int columns MEMBER columns NOTIFY columnChanged)

  explicit BoardViewModel(QObject* parent = nullptr);

  void initWithDimension(int row, int col) override {
    spdlog::info("row: {}, col: {}", row, col);
  }

  void present(common::Actions actions) override {
    spdlog::info("present actions: {}", actions);
    for (const auto& [from, to] : actions.moveActions) {
      Q_ASSERT(from != to);
      emit startCellMove(from.row, from.col, to.row, to.col);
    }
    QTimer::singleShot(100, [this, actions = std::move(actions)]() {
      for (const auto& [from, to] : actions.moveActions) {
        emit completeCellMove(from.row, from.col, to.row, to.col);
      }
      for (const auto& [pos, toValue] : actions.mergeActions) {
        emit mergeCell(pos.row, pos.col, QString::number(toValue));
      }
      for (const auto& [pos, value] : actions.newActions) {
        emit newCell(pos.row, pos.col, QString::number(value));
      }
    });
  }

  Q_INVOKABLE void restart() { controller.newGame(); }

  Q_INVOKABLE void swipe(int key) { controller.swipe(directionMap.at(key)); }

 signals:
  void rowsChanged();
  void columnChanged();

  void newCell(int row, int col, QString value);
  void startCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void completeCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void mergeCell(int row, int col, QString toValue);

 private:
  int rows = 4;
  int columns = 4;

  presenter::Controller controller;
  presenter::BoardPresenter boardPresenter;

  inline static const std::unordered_map<int, common::Direction> directionMap{
      {Qt::Key_Left, common::Direction::left},
      {Qt::Key_Right, common::Direction::right},
      {Qt::Key_Up, common::Direction::up},
      {Qt::Key_Down, common::Direction::down},
  };
};  // namespace qt_view_model

}  // namespace qt_view_model

#endif
