import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick3D
import QtQuick.Controls
// import com.projectdissolve

ApplicationWindow {
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
        Model { source: "#Cube" }
        Model {
            source: LineGeometry {
              id: basicLine
            }
            materials: [
                DefaultMaterial {
                    diffuseColor: Qt.rgba(0.8, 0.8, 0.8, 1.0)
                }
            ]
        }
    }

    View3D {
           id: graphView
           anchors.fill: parent

           camera: OrthographicCamera {
                   id: cameraOrthographicLeft
                   x: -600
                   eulerRotation.y: -90
           }
           importScene: standAloneScene
    }
}
