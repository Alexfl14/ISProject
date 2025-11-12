# 1. Find the testing framework (gtest)
find_package(GTest CONFIG REQUIRED)

# 2. Define the test executable
add_executable(SokobanTests
        pch.h
        pch.cpp

)

# 3. Link dependencies
# Link privately to the Core library and the testing framework
target_link_libraries(SokobanTests
        PRIVATE
        SokobanCore
        GTest::gtest_main
)

# Set include directories for PCH and test headers
target_include_directories(SokobanTests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
