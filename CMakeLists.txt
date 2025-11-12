cmake_minimum_required(VERSION 3.15)
project(SokobanGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Note: The CMAKE_TOOLCHAIN_FILE variable must be set in your CLion
# CMake settings or passed via command line to enable vcpkg.

# This allows Visual Studio to see the projects correctly grouped
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT SokobanUI)

add_subdirectory(SokobanCore)
add_subdirectory(SokobanTests)
add_subdirectory(SokobanUI)