#include "axisTickLabels.h"
#include "axis.h"
#include <iostream>

AxisTickLabels::AxisTickLabels(Axis &parent) : parent_(parent) {}

int AxisTickLabels::rowCount([[maybe_unused]] const QModelIndex &parent) const { return parent_.tickCount(); }

QVariant AxisTickLabels::data(const QModelIndex &index, int role) const
{
    std::cout << "New Data: " << index.row() << " " << (role - Qt::UserRole) << std::endl;
    switch (role)
    {
        case Qt::UserRole:
            std::cout << parent_.tick(index.row()) << std::endl;
            return QString("%1").arg(parent_.tick(index.row()));
        case (Qt::UserRole + 1):
            return parent_.direction() ? parent_.tickCoord(index.row()) : 0;
        case (Qt::UserRole + 2):
            return parent_.direction() ? 0 : parent_.tickCoord(index.row());
        default:
            return index.row();
    }
}

QHash<int, QByteArray> AxisTickLabels::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "tickLabel";
    roles[Qt::UserRole + 1] = "tickX";
    roles[Qt::UserRole + 2] = "tickY";
    return roles;
}

void AxisTickLabels::reset()
{
    beginResetModel();
    endResetModel();
}
