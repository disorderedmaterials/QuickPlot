// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include <QAbstractListModel>

class Axis;

/** A list model that provides the tick labels of the axis */
class AxisTickLabels : public QAbstractListModel
{
    Q_OBJECT

    public:
    AxisTickLabels(Axis &parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    /** Function to reset the model (and trigger redrawing all labels */
    void reset();

    private:
    Axis &parent_;
};
