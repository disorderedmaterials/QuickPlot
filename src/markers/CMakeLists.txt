add_library(markers marker.h marker.cpp cube.h cube.cpp diamond.h diamond.cpp)

target_include_directories(markers PRIVATE ${PROJECT_SOURCE_DIR}/src)
