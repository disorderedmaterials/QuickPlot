import QtQuick
import QtQuick3D
import com.projectdissolve

Node {
    id: root
    required property Axis axis
    required property vector3d scl
    property color color

    Model {
        geometry: root.axis 
        materials: [
            PrincipledMaterial {
                id: frame_material
                baseColor: root.color
                alphaMode: PrincipledMaterial.Opaque
            }
        ]
        scale: root.scl
    }

    Repeater3D {
        id: rep
        model: axis.tickLabels
        delegate: Node{
            position: axis.direction ? Qt.vector3d(-root.scl.x + 2 * tickX * root.scl.x/(rep.count - 1), -root.scl.y - 210, 0) : Qt.vector3d(-root.scl.x - 30, -root.scl.y -180 + 2 * tickY * root.scl.y/(rep.count - 1), 0)
            /* position: axis.direction ? Qt.vector3d(-root.scl.x + 2 * index * root.scl.x / (rep.count - 1), -root.scl.y - 210, 0) : Qt.vector3d(-root.scl.x - 30.0, -root.scl.y - 180 + 2 * index * root.scl.y / (rep.count - 1), 0) */
            Item {
                /* required property int index */
                width: 400
                height: 400
                anchors.centerIn: parent

                Text {
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 20
                    color: root.color
                    text: tickLabel
                }
            }
        }
    }
}
