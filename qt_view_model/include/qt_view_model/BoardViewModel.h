#ifndef CLEAN2048_QTVIEWMODEL_BOARDVIEWMODEL_H_
#define CLEAN2048_QTVIEWMODEL_BOARDVIEWMODEL_H_

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <QKeyEvent>
#include <QObject>
#include <QString>
#include <QTimer>

#include "common/ModelHelper.h"
#include "presenter/BoardPresenter.h"

namespace qt_view_model {

class BoardViewModel : public QObject, presenter::BoardPresenterDelegate {
  Q_OBJECT

  Q_PROPERTY(int rows MEMBER rowsCache NOTIFY rowsChanged)
  Q_PROPERTY(int cols MEMBER colsCache NOTIFY colsChanged)

 public:
  explicit BoardViewModel(QObject* parent = nullptr);

  void initWithDimension(int rows, int cols) override {
    spdlog::info("initWithDimension: rows: {}, cols: {}", rows, cols);
    rowsCache = rows;
    colsCache = cols;
    emit initWith(rows, cols);
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

 signals:
  void rowsChanged(int rows);
  void colsChanged(int cols);
  void initWith(int rows, int cols);
  void newCell(int row, int col, QString value);
  void startCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void completeCellMove(int fromRow, int fromCol, int toRow, int toCol);
  void mergeCell(int row, int col, QString toValue);

 private:
  presenter::BoardPresenter boardPresenter;

  int rowsCache = 0;
  int colsCache = 0;
};

}  // namespace qt_view_model

#endif
