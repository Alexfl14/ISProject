//
// Created by fafa on 12.11.2025.
//

#include "GameMap.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

GameMap::GameMap() : _playerStart(0, 0), _width(0), _height(0) {}

void GameMap::load(int levelNumber) {
    // Read JSON file
    std::ifstream file("levels.json");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open levels.json");
    }
    
    json data;
    file >> data;
    file.close();
    
    // Find the level with matching ID
    bool levelFound = false;
    for (const auto& level : data["levels"]) {
        if (level["id"] == levelNumber) {
            levelFound = true;
            
            // Load dimensions
            _width = level["width"];
            _height = level["height"];
            
            // Load grid
            _grid.clear();
            _grid.resize(_height);
            
            const auto& gridData = level["grid"];
            for (int row = 0; row < _height; ++row) {
                _grid[row].clear();
                for (int col = 0; col < _width; ++col) {
                    int tileValue = gridData[row][col];
                    _grid[row].emplace_back(static_cast<ETileType>(tileValue));
                }
            }
            
            // Load player start position
            const auto& playerStartData = level["playerStart"];
            _playerStart.setRow(playerStartData["row"]);
            _playerStart.setCol(playerStartData["col"]);
            
            // Load box positions
            _boxPositions.clear();
            const auto& boxPositionsData = level["boxPositions"];
            for (const auto& boxPos : boxPositionsData) {
                _boxPositions.emplace_back(boxPos["row"], boxPos["col"]);
            }
            
            break;
        }
    }
    
    if (!levelFound) {
        throw std::runtime_error("Level " + std::to_string(levelNumber) + " not found");
    }
}

int GameMap::getWidth() const {
    return _width;
}

int GameMap::getHeight() const {
    return _height;
}

ETileType GameMap::getTileAt(int row, int col) const {
    if (row < 0 || row >= _height || col < 0 || col >= _width) {
        throw std::out_of_range("Position out of bounds");
    }
    return _grid[row][col].getTileType();
}

Position GameMap::getPlayerStart() const {
    return _playerStart;
}

std::vector<Position> GameMap::getBoxPositions() const {
    return _boxPositions;
}
