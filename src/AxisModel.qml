import QtQuick
import QtQuick3D
import com.projectdissolve

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
            position: axis.direction ? Qt.vector3d(-root.scl.x + 2 * tickX * root.scl.x / (rep.count - 1), -root.scl.y - 210, 0) : Qt.vector3d(-root.scl.x - 30, -root.scl.y - 180 + 2 * tickY * root.scl.y / (rep.count - 1), 0)

            /* position: axis.direction ? Qt.vector3d(-root.scl.x + 2 * index * root.scl.x / (rep.count - 1), -root.scl.y - 210, 0) : Qt.vector3d(-root.scl.x - 30.0, -root.scl.y - 180 + 2 * index * root.scl.y / (rep.count - 1), 0) */
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
