cmake_minimum_required(VERSION 3.20)
project(SokobanTests)

# 1. Find all source files
file(GLOB_RECURSE TESTS_SOURCES "src/*.cpp")

# 2. Create Executable
add_executable(SokobanTests 
    ${TESTS_SOURCES}
 "src/core_tests/PlayerTest.cpp" "src/core_tests/GameTest.cpp" "src/core_tests/PositionTest.cpp" "src/core_tests/TileTest.cpp")

# 3. PRECOMPILED HEADERS (Vital for your pch.h to work)
# This tells CMake to use src/pch.h for every file in this project
target_precompile_headers(SokobanTests PRIVATE src/core_tests/pch.h)
# 4. Link Dependencies
target_link_libraries(SokobanTests
    PRIVATE
    SokobanCore       # Ensure this matches your Core project name exactly
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)

# 5. Include Directories
target_include_directories(SokobanTests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/SokobanUI/include
)

# 6. Compiler Warnings
if(MSVC)
    target_compile_options(SokobanTests PRIVATE /W4)
else()
    target_compile_options(SokobanTests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 7. Register Tests
include(GoogleTest)
gtest_discover_tests(SokobanTests
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    PROPERTIES
    LABELS "unit"
)

# REMOVED: The add_custom_command for copying test_data
# Reason: You don't have a test_data folder, and your code generates its own levels.json.