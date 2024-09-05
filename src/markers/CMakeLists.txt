add_library(markers marker.h cube.h cube.cpp)

target_include_directories(markers PRIVATE ${PROJECT_SOURCE_DIR}/src)
