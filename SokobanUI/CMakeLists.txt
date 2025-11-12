# 1. Find the Raylib UI framework
# Raylib does not provide a CONFIG file, so we use the simpler find_package
# with the name it installs. (vcpkg provides it via the pkg-config file)
find_package(raylib CONFIG REQUIRED)

# 2. Define the UI executable
add_executable(SokobanUI
        GUI_View.cpp
        GUI_View.h
)

# 3. Link dependencies
# Link privately to the Core library and the Raylib library
target_link_libraries(SokobanUI
        PRIVATE
        SokobanCore
        raylib
)

# Optional: Set a target property for Visual Studio to organize files
source_group("Header Files" FILES ${UI_HEADERS})
source_group("Source Files" FILES ${UI_SOURCES})