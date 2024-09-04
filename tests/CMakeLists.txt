cmake_policy(SET CMP0054 NEW)
find_package(GTest REQUIRED)
include(GoogleTest)

set(SOURCES axis.cpp triangles.cpp quads.cpp)
add_executable(axis ${SOURCES})

target_include_directories(
  axis
  PUBLIC ${PROJECT_SOURCE_DIR}/src
  PRIVATE ${PROJECT_SOURCE_DIR}/lib ${PROJECT_BINARY_DIR}/lib
          ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Quick3D_INCLUDE_DIRS})
target_link_libraries(
  axis
  PUBLIC QuickPlot
  PRIVATE # External libs
          GTest::gtest_main Qt6::Core Qt6::Quick3D)

gtest_discover_tests(axis)
