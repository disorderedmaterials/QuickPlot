\mainpage

# Introduction

QuickPlot is a charting library for QML.  It has just recently started
and is actively under heavy development.  Currently, we are not
competitive with QtChart, but we hope to reach that point.

# Concepts

## Spaces

This library is based around converting data between two different spaces.

### Data Space
  The values of the data points.  These are the real world
  measurements that you want to visualise in the plot.  All off the
  PlotGeometry descendents expect for their data to be given in data
  space coordinates.

### Chart Space
  The location in the graph.  The chart space goes from -1 to 1 along
  the X, Y, and Z axes.  An Axis (or a subclass there of) is used to
  convert data from the data space into the chart space.  Only
  developers creating new axes and geometries should ever need to
  think about chart space.

# QML

The simplest chart will need two axes for the X and Y coordinates.  A
chart can handle any number of axes, but each data plot will require
at least two axes to plot.  The axis is declared via the AxisModel.

```qml
axis: Axis {
    id: xAxis
    direction: true
    thickness: 0.01
}
```

The axis requires a direction (which will eventually be an Enum, but
it currently just a boolean) and a thickness. To plot the axis in the
chart, wrap it within an AxisModel.  It will need a `color` (probably
black) and a `scl`, which represents the size of the canvas.  The
scale ensures that the graph can be safely resized.

```qml
AxisModel {
    color: "black"
    scl: root.scale
    axis: xAxis
}
```

The data can then be plotted with a `LineModel` or a `ScatterModel`.
Just as with the axes, the data will need a `thickness` and a `scale`.
It will also need to be object identifiers of the X and Y axis.
Finally, the X and Y coordinates of the data points should be assigned
to the `xs` and `ys` properties.

```qml
LineModel {
    color: "#006f6f"
    scale: root.scale
    thickness: thickness.value
    xAxis: xAxis
    xs: [-1.0, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1.0]
    yAxis: yAxis
    ys: [1.0, 0.64, 0.36, 0.16, 0.04, 0, 0.04, 0.16, 0.36, 0.64, 1.0]
}
```

Every item that should appear in the chart (e.g. LineModel, AxisModel)
need to be children of the same `Node` element (which we named
`standAloneScene` in the example below).  This node can be the
`importScene` of a `View3D`.  The view will also need an
OrthographicCamera to prevent perspective distortions.  Finally, a
mouse area can optionally connect to the `nudge` methods on the axes
to enable easy scrolling of the plot.

```qml
View3D {
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
}
```
