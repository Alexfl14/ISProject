#include "pch.h"


// Helper to create a temporary levels.json file for testing
void WriteTestLevelsJson(const std::string& filename) {
    nlohmann::json j;
    j["levels"] = {
        {
            {"id", 1},
            {"width", 3},
            {"height", 2},
            {"grid", {{0, 1, 2}, {2, 1, 0}}},
            {"playerStart", {{"row", 1}, {"col", 2}}},
            {"boxPositions", {{{"row", 0}, {"col", 1}}, {{"row", 1}, {"col", 0}}}}
        }
    };
    std::ofstream out(filename);
    out << j.dump();
    out.close();
}

class GameMapTest : public ::testing::Test {
protected:
    void SetUp() override {
        WriteTestLevelsJson("levels.json");
    }
    void TearDown() override {
        std::remove("levels.json");
    }
};

TEST_F(GameMapTest, LoadValidLevel) {
    GameMap map;
    EXPECT_NO_THROW(map.load(1));
    EXPECT_EQ(map.getWidth(), 3);
    EXPECT_EQ(map.getHeight(), 2);

    // Check grid tiles
    EXPECT_EQ(map.getTileAt(0, 0), ETileType::PATH);
    EXPECT_EQ(map.getTileAt(0, 1), ETileType::TARGET);
    EXPECT_EQ(map.getTileAt(0, 2), ETileType::WALL);
    EXPECT_EQ(map.getTileAt(1, 0), ETileType::WALL);
    EXPECT_EQ(map.getTileAt(1, 1), ETileType::TARGET);
    EXPECT_EQ(map.getTileAt(1, 2), ETileType::PATH);

    // Check player start
    Position start = map.getPlayerStart();
    EXPECT_EQ(start.getRow(), 1);
    EXPECT_EQ(start.getCol(), 2);

    // Check box positions
    auto boxes = map.getBoxPositions();
    ASSERT_EQ(boxes.size(), 2);
    EXPECT_EQ(boxes[0], Position(0, 1));
    EXPECT_EQ(boxes[1], Position(1, 0));
}

TEST_F(GameMapTest, LoadMissingFileThrows) {
    std::remove("levels.json");
    GameMap map;
    EXPECT_THROW(map.load(1), std::runtime_error);
}

TEST_F(GameMapTest, LoadMissingLevelThrows) {
    GameMap map;
    EXPECT_THROW(map.load(999), std::runtime_error);
}

TEST_F(GameMapTest, GetTileAtOutOfBoundsThrows) {
    GameMap map;
    map.load(1);
    EXPECT_THROW(map.getTileAt(-1, 0), std::out_of_range);
    EXPECT_THROW(map.getTileAt(0, -1), std::out_of_range);
    EXPECT_THROW(map.getTileAt(2, 0), std::out_of_range);
    EXPECT_THROW(map.getTileAt(0, 3), std::out_of_range);
}

TEST_F(GameMapTest, DefaultConstructorInitializesMembers) {
    GameMap map;
    EXPECT_EQ(map.getWidth(), 0);
    EXPECT_EQ(map.getHeight(), 0);
    Position start = map.getPlayerStart();
    EXPECT_EQ(start.getRow(), 0);
    EXPECT_EQ(start.getCol(), 0);
    EXPECT_TRUE(map.getBoxPositions().empty());
}
