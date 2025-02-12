// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2024 Team Dissolve and contributors

import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import ProjectDissolve
import "../ProjectDissolve"

ApplicationWindow {
    id: root

    property vector3d scale: Qt.vector3d(Math.min(graphView.width / 2.5, graphView.height / 2.5), Math.min(graphView.width / 2.5, graphView.height / 2.5), Math.min(graphView.width / 2.5, graphView.height / 2.5))

    height: 600
    title: "Mildred QML Test"
    visible: true
    width: 800

    Node {
        id: standAloneScene

        DirectionalLight {
            ambientColor: Qt.rgba(0.5, 0.5, 0.5, 1.0)
            brightness: 1.0
            eulerRotation.x: -25
        }
        ScatterModel {
            id: plotLine

            color: colorDialog.selectedColor
            scale: root.scale
            thickness: thickness.value
            xAxis: xAxis
            yAxis: yAxis
        }
        LineModel {
            color: "#006f6f"
            scale: root.scale
            thickness: thickness.value
            xAxis: xAxis
            xs: [-1.0, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1.0]
            yAxis: yAxis
            ys: [1.0, 0.64, 0.36, 0.16, 0.04, 0, 0.04, 0.16, 0.36, 0.64, 1.0]
        }
        AxisModel {
            color: "black"
            scl: root.scale

            axis: Axis {
                id: xAxis

                direction: Axis.X
                thickness: 0.01
            }
        }
        AxisModel {
            color: "black"
            scl: root.scale

            axis: LogAxis {
                id: yAxis

                direction: Axis.Y
                maximum: 1.0
                minimum: 0.01
                thickness: 0.01
            }
        }
        AxisModel {
            color: "black"
            scl: root.scale

            axis: Axis {
                id: zAxis

                direction: Axis.Z
                thickness: 0.01
            }
        }
    }
    View3D {
        id: graphView

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: settingsPane.left
        anchors.top: parent.top
        importScene: standAloneScene

        camera: OrthographicCamera {
            id: cameraOrthographicLeft

            z: 600
        }

        MouseArea {
            anchors.fill: parent

            onWheel: function (event) {
                xAxis.nudge(0.01 * event.pixelDelta.x);
                yAxis.nudge(-0.01 * event.pixelDelta.y);
            }
        }
        OrbitCameraController {
            anchors.fill: parent
            camera: cameraOrthographicLeft
            origin: standAloneScene
        }
    }
    Pane {
        id: settingsPane

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        width: 200

        Column {
            Label {
                text: "Thickness"
            }
            Slider {
                id: thickness

                from: 0.01
                to: 0.1
            }
            Label {
                text: "Count"
            }
            Slider {
                id: count

                from: 10
                to: 1000
                value: 20

                onMoved: renderButton.onClicked()
            }
            Label {
                text: "Amplitude"
            }
            Slider {
                id: amplitude

                from: 0
                to: 5
                value: 1

                onMoved: renderButton.onClicked()
            }
            Label {
                text: "Frequency"
            }
            Slider {
                id: frequency

                from: 0
                to: 10
                value: 3

                onMoved: renderButton.onClicked()
            }
            ColorDialog {
                id: colorDialog

                selectedColor: "#ff00ff"
            }
            Button {
                text: "Color"

                onClicked: colorDialog.open()
            }
            Button {
                id: renderButton

                text: "render"

                onClicked: {
                    var xs = [];
                    var ys = [];
                    for (var i = 0; i < count.value; i++) {
                        var x = -1.0 + 2 * i / count.value;
                        xs.push(x);
                        ys.push(amplitude.value * Math.sin(frequency.value * Math.PI * x));
                    }
                    plotLine.xs = xs;
                    plotLine.ys = ys;
                }
            }
        }
    }
}
