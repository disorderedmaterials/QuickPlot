// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

#pragma once

#include <QAbstractListModel>

class Axis;

class AxisTickLabels : public QAbstractListModel
{
    Q_OBJECT

    public:
    AxisTickLabels(Axis &parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int tickCount() const;
    void setTickCount(const int count);
    void reset();

    private:
    Axis &parent_;
};
