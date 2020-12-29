#include "CellView.h"

#include <QPropertyAnimation>
#include <unordered_map>

#include "ui_CellView.h"

const std::unordered_map<QString, QString> backgroundMap{
    {"2", "#eee4da"},    {"4", "#ece0c8"},     {"8", "#f2b179"},
    {"16", "#f59563"},   {"32", "#f57c5f"},    {"64", "#f95c3b"},
    {"128", "#edce71"},  {"256", "#eecc61"},   {"512", "#ebc850"},
    {"1024", "#edc53f"}, {"2048", "#eec22e"},  {"4096", "#3d3a33"},
    {"8192", "#3d3a33"}, {"16384", "#3d3a33"},
};

const std::unordered_map<int, QString> fontSizeMap{
    {1, "45"},
    {2, "40"},
    {3, "35"},
    {4, "30"},
};

CellView::CellView(QWidget *parent) : QWidget(parent), ui(new Ui::CellView) {
  ui->setupUi(this);
}

CellView::~CellView() { delete ui; }

void CellView::setText(const QString &value) {
  ui->label->setText(value);
  QString color{value == "2" || value == "4" ? "#786f66" : "#f7f8f0"};
  ui->label->setStyleSheet(
      "background: " + backgroundMap.at(value) + "; color: " + color +
      "; font-size: " + fontSizeMap.at(value.length()) + "px;");
}
