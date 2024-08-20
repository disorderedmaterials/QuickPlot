// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#include "axisTickLabels.h"
#include "axis.h"
#include <iostream>

AxisTickLabels::AxisTickLabels(Axis &parent) : parent_(parent) {}

int AxisTickLabels::rowCount([[maybe_unused]] const QModelIndex &parent) const { return parent_.tickCount(); }

QVariant AxisTickLabels::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
        case Qt::UserRole:
            return QString("%1").arg(parent_.tick(index.row()));
        case (Qt::UserRole + 1):
            return (parent_.direction() == Axis::Direction::X) ? parent_.tickCoord(index.row()) : 0;
        case (Qt::UserRole + 2):
            return (parent_.direction() == Axis::Direction::X) ? 0 : parent_.tickCoord(index.row());
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
