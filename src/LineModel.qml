import QtQuick
import QtQuick3D
import com.projectdissolve

Model {
    id: root

    property color color
    property double thickness
    property Axis xAxis
    property list<double> xs
    property Axis yAxis
    property list<double> ys

    Connections {
        target: xAxis
        function onDataChanged() {
            plotLine.dataChanged();
        }
    }
    Connections {
        target: yAxis
        function onDataChanged() {
            plotLine.dataChanged();
        }
    }

    geometry: LineGeometry {
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
}
