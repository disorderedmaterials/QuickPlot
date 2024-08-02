// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

import QtQuick
import QtQuick3D
import ProjectDissolve

Model {
    id: root

    property color color
    property double thickness
    property Axis xAxis
    property list<double> xs
    property Axis yAxis
    property list<double> ys

    geometry: ScatterGeometry {
        id: plotLine

        thickness: root.thickness
        xAxis: root.xAxis
        xs: root.xs
        yAxis: root.yAxis
        ys: root.ys
    }
    materials: [
        PrincipledMaterial {
            id: frame_material

            alphaMode: PrincipledMaterial.Opaque
            baseColor: root.color
        }
    ]

    Connections {
        function onDataChanged() {
            plotLine.dataChanged();
        }

        target: xAxis
    }
    Connections {
        function onDataChanged() {
            plotLine.dataChanged();
        }

        target: yAxis
    }
}
