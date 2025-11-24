cmake_minimum_required(VERSION 3.20)
project(SokobanTests)

# Explicitly list all test files (NO SimpleTest.cpp)
set(TEST_SOURCES
    src/core_tests/GameMapTest.cpp
    src/core_tests/GameObjectTest.cpp
    src/core_tests/GameTest.cpp
    src/core_tests/PlayerTest.cpp
    src/core_tests/PositionTest.cpp
    src/core_tests/TileTest.cpp
)

# Create Executable
add_executable(SokobanTests ${TEST_SOURCES})

# Link Dependencies
target_link_libraries(SokobanTests
    PRIVATE
    SokobanCore
    GTest::gtest
    GTest::gtest_main
)

# Include Directories
target_include_directories(SokobanTests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/SokobanCore/include
    ${CMAKE_SOURCE_DIR}/SokobanUI/include
)

# Compiler options
if(MSVC)
    target_compile_options(SokobanTests PRIVATE /W4)
else()
    target_compile_options(SokobanTests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# USE add_test() NOT gtest_discover_tests()
enable_testing()
add_test(NAME SokobanTests COMMAND SokobanTests)
