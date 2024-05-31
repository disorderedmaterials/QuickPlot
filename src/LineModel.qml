import QtQuick
import QtQuick3D
import com.projectdissolve

Model {
    id: root
    property double thickness
    property list<double> xs
    property list<double> ys
    property Axis xAxis
    property Axis yAxis
    property color color

    geometry: LineGeometry {
        id: plotLine
        thickness: root.thickness
        xs: root.xs
        ys: root.ys
        xAxis: root.xAxis
        yAxis: root.yAxis
    }
    materials: [
        PrincipledMaterial {
            id: frame_material
            baseColor: root.color
            alphaMode: PrincipledMaterial.Opaque
        }
    ]
}
