# Define the static library
add_library(SokobanCore STATIC
        Enums/EGameState.h
        Enums/EFacing.h
        Enums/ETileType.h
        Enums/EGameEvent.h

        Interfaces/IGame.h
        Interfaces/IGameMap.h
        Interfaces/IGameSubject.h
        Interfaces/IGameObserver.h
        Interfaces/IGameObject.h

        Game/Position.h
        Game/Tile.h
        Game/Game.h
        Game/Game.cpp
        Game/GameMap.h
        Game/GameMap.cpp

        Objects/Player.h
        Objects/Player.cpp
        Objects/Box.h
        Objects/Box.cpp
        Interfaces/IGameMap.h
)

# Set include directories for the library. PUBLIC exports headers to targets
# that link to SokobanCore (Tests and UI).
target_include_directories(SokobanCore
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Find and link dependencies required by the core logic
# nlohmann-json is a header-only library, but linking it is good practice
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(SokobanCore
        PUBLIC
        nlohmann_json::nlohmann_json
)

# Optional: Set a target property for Visual Studio to organize headers in the IDE
source_group("Header Files" FILES ${CORE_HEADERS})
source_group("Source Files" FILES ${CORE_SOURCES})