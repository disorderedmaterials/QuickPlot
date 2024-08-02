// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

import QtQuick
import QtQuick3D
import ProjectDissolve

Node {
    id: root

    required property Axis axis
    property color color
    required property vector3d scl

    Model {
        geometry: root.axis
        scale: root.scl

        materials: [
            PrincipledMaterial {
                id: frame_material

                alphaMode: PrincipledMaterial.Opaque
                baseColor: root.color
            }
        ]
    }
    Repeater3D {
        id: rep

        model: axis.tickLabels

        delegate: Node {
            position: axis.direction ? Qt.vector3d(-root.scl.x + tickX * root.scl.x, -root.scl.y - 210, 0) : Qt.vector3d(-root.scl.x - 30, -root.scl.y - 180 + tickY * root.scl.y, 0)

            Item {
                anchors.centerIn: parent
                height: 400
                /* required property int index */
                width: 400

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    color: root.color
                    font.pixelSize: 20
                    text: tickLabel
                }
            }
        }
    }
}
