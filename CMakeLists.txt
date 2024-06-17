cmake_minimum_required(VERSION 3.15)
project(mildred)

set(DESCRIPTION "Mildred - graphing / plotting leveraging Qt3D")
set(AUTHOR "T. Youngs")
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set policy for automatic linkage of Qt libs to project
cmake_policy(SET CMP0020 NEW)

# Request C++17 Standard Support (Required for std::optional and auto types in
# lambda parameters)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
  set(CMAKE_PREFIX_PATH "${QT_BASE_DIR}")
endif(APPLE)

find_package(OpenGL REQUIRED)
find_package(
  Qt6
  COMPONENTS Core
             Gui
             Widgets
             Qml
             Quick3D
             3DCore
             3DExtras
             3DRender
             3DExtras
  REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# -- Windows
if(WIN32)
  # Add defines for Windows systems - NOMINMAX to prevent conflicts with
  # std::min() and std::max()
  add_definitions(-DNOMINMAX)
  add_definitions(/Zc:__cplusplus)
endif(WIN32)

# -- Unix
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Werror -Wall -Wextra")
endif(UNIX)

# -- OSX
if(APPLE)
  # Set some specific C++11 related options here (set_property below does not
  # seem to persist)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

  add_definitions(-D_MAC)
endif(APPLE)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Add main library subdir
add_subdirectory(src/)
