cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE TESTS_SOURCES "src/*.cpp")

# SokobanTests executable
add_executable(SokobanTests 
        ${TESTS_SOURCES}
)

# Link dependencies
target_link_libraries(SokobanTests
        PRIVATE
        Sokoban::Core
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
)

# Include directories
target_include_directories(SokobanTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/SokobanUI/include
)

# Compiler warnings
if(MSVC)
    target_compile_options(SokobanTests PRIVATE /W4)
else()
    target_compile_options(SokobanTests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(SokobanTests
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        PROPERTIES
        LABELS "unit"
)

# Copy test data to build directory
add_custom_command(TARGET SokobanTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/test_data
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data
        COMMENT "Copying test data to build directory"
)