#include "pch.h"
#include "GameMap.h"
#include "enums/ETileType.h"

// Helper to write JSON 
void WriteTestLevelsJson(const std::string& filename) {
    nlohmann::json j;
    j["levels"] = {
        {
            {"id", 1},
            {"width", 3},
            {"height", 2},
            {"grid", {{0, 1, 2},
                    {2, 1, 0}}}, // 0=Path, 1=Wall, 2=Target
            {"playerStart", {{"row", 1}, {"col", 2}}},
            {"boxPositions", {{{"row", 0}, {"col", 1}}}}
        }
    };
    std::ofstream out(filename);
    out << j.dump();
    out.close();
}

class GameMapTest : public ::testing::Test {
protected:
    void SetUp() override { WriteTestLevelsJson("levels.json"); }
    void TearDown() override { std::remove("levels.json"); }
};

TEST_F(GameMapTest, LoadCorrectlyParsesGrid) {
    GameMap map;
    map.load(1);

    EXPECT_EQ(map.getWidth(), 3);
    EXPECT_EQ(map.getHeight(), 2);

    // 0=Path
    EXPECT_EQ(map.getTileAt(0, 0), ETileType::PATH);
    // 2=Target
    EXPECT_EQ(map.getTileAt(0, 1), ETileType::TARGET);
}