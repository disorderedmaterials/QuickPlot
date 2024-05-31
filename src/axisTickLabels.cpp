#include "axisTickLabels.h"
#include "axis.h"
#include <iostream>

AxisTickLabels::AxisTickLabels(Axis &parent) : parent_(parent), N_(5) {}

int AxisTickLabels::tickCount() const { return N_; }

void AxisTickLabels::setTickCount(const int count) {
  beginResetModel();
  N_ = count;
  endResetModel();
}

int AxisTickLabels::rowCount([[maybe_unused]] const QModelIndex &parent) const { return N_; }

QVariant AxisTickLabels::data(const QModelIndex &index, int role) const {
  switch (role) {
  case Qt::UserRole:
    return QString("%1").arg(parent_.minimum() +
                             index.row() / ((double)N_ - 1) *
                                 (parent_.maximum() - parent_.minimum()));
  case (Qt::UserRole + 1):
    return parent_.direction() ? index.row() : 0;
  case (Qt::UserRole + 2):
    return parent_.direction() ? 0 : index.row();
  default:
    return index.row();
  }
}

QHash<int, QByteArray> AxisTickLabels::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Qt::UserRole] = "tickLabel";
  roles[Qt::UserRole + 1] = "tickX";
  roles[Qt::UserRole + 2] = "tickY";
  return roles;
}
