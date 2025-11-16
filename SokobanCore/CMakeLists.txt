cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")
file(GLOB_RECURSE CORE_HEADERS_FOR_COMPILATION "include/*.h" "include/*.hpp")
list(APPEND CORE_SOURCES ${CORE_HEADERS_FOR_COMPILATION})

# SokobanCore library
add_library(SokobanCore STATIC
        ${CORE_SOURCES}
)

# Create alias for consistent naming
add_library(Sokoban::Core ALIAS SokobanCore)

# Include directories
target_include_directories(SokobanCore
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(SokobanCore
        PUBLIC
        nlohmann_json::nlohmann_json
)

# Compiler warnings
if(MSVC)
    target_compile_options(SokobanCore PRIVATE /W4)
else()
    target_compile_options(SokobanCore PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Installation rules (optional, for later)
install(TARGETS SokobanCore
        EXPORT SokobanCoreTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/
        DESTINATION include
)