add_subdirectory(markers/)

qt_add_qml_module(
  QuickPlot
  URI
  ProjectDissolve
  VERSION
  1.0
  STATIC
  SOURCES
  axis.h
  axis.cpp
  axisTickLabels.h
  axisTickLabels.cpp
  lineGeometry.cpp
  lineGeometry.h
  logAxis.h
  logAxis.cpp
  plotGeometry.h
  plotGeometry.cpp
  scatterGeometry.cpp
  scatterGeometry.h
  solid.h
  solid.cpp
  triangle.cpp
  QML_FILES
  AxisModel.qml
  LineModel.qml
  ScatterModel.qml)

target_include_directories(
  QuickPlot PRIVATE ${PROJECT_SOURCE_DIR}/lib ${PROJECT_BINARY_DIR}/lib
                    ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Quick3D_INCLUDE_DIRS})

target_link_libraries(QuickPlot PRIVATE markers)

set_target_properties(QuickPlot PROPERTIES PUBLIC_HEADER lineGeometry.h)

install(TARGETS QuickPlot QuickPlotplugin)

option(BUILD_DEMO "Build Demo Executable" OFF)
if(BUILD_DEMO)
  # Main target
  qt_add_executable(demo main.cpp)
  qt_add_qml_module(
    demo
    VERSION
    1.0
    URI
    PlotDemo
    QML_FILES
    main.qml)

  target_include_directories(
    demo
    PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR}/src
            ${PROJECT_SOURCE_DIR}/lib ${PROJECT_BINARY_DIR}/lib
            ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Quick3D_INCLUDE_DIRS})

  target_link_libraries(
    demo
    PRIVATE QuickPlot
            QuickPlotplugin
            Qt6::Widgets
            Qt6::Gui
            Qt6::Qml
            Qt6::Core
            Qt6::Quick3D)

  set_target_properties(demo PROPERTIES RUNTIME demo)

  install(TARGETS demo RUNTIME)

endif(BUILD_DEMO)
