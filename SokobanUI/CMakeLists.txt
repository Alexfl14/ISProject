cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE UI_SOURCES "src/*.cpp")
file(GLOB_RECURSE UI_HEADERS_FOR_COMPILATION "include/*.h" "include/*.hpp")
list(APPEND UI_SOURCES ${UI_HEADERS_FOR_COMPILATION})

# SokobanUI executable
add_executable(SokobanUI
        ${UI_SOURCES}
 "main.cpp")

# Link dependencies
target_link_libraries(SokobanUI
        PRIVATE
        Sokoban::Core
        raylib
)

# Include directories
target_include_directories(SokobanUI
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Compiler warnings
if(MSVC)
    target_compile_options(SokobanUI PRIVATE /W4)
else()
    target_compile_options(SokobanUI PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Copy assets to build directory
add_custom_command(TARGET SokobanUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
        COMMENT "Copying assets to build directory"
)

# Installation rules
install(TARGETS SokobanUI
        RUNTIME DESTINATION bin
)

install(DIRECTORY assets/
        DESTINATION bin/assets
)