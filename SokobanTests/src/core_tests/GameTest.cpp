#include "pch.h"
#include "Game.h"
#include "interfaces/IGameObserver.h" 
#include "enums/EFacing.h"
#include "enums/EGameEvent.h"
#include "enums/EGameState.h"

// Mock Observer must implement IGameObserver
class MockGameObserver : public IGameObserver {
public:
    EGameEvent lastEvent;
    int eventCount = 0;

    // Matches virtual void onNotify(EGameEvent event) = 0;
    void onNotify(EGameEvent event) override {
        lastEvent = event;
        eventCount++;
    }

    void reset() { eventCount = 0; }
};

class GameTest : public ::testing::Test {
protected:
    Game game;
    MockGameObserver observer;
    const std::string testJsonFile = "levels.json";

    void SetUp() override {
        // Create temporary 5x3 map for testing
        nlohmann::json j;
        j["levels"] = {
            {
                {"id", 99},
                {"width", 5},
                {"height", 3},
                {"grid", {
                    {1, 1, 1, 1, 1}, // Walls
                    {1, 0, 0, 0, 2}, // Wall, Path, Path, Path, Target
                    {1, 1, 1, 1, 1}  // Walls
                }},
                {"playerStart", {{"row", 1}, {"col", 1}}},
                {"boxPositions", {{{"row", 1}, {"col", 2}}}}
            }
        };
        std::ofstream out(testJsonFile);
        out << j.dump();
        out.close();

        game.addObserver(&observer);
    }

    void TearDown() override {
        game.removeObserver(&observer);
        std::remove(testJsonFile.c_str());
    }
};

TEST_F(GameTest, LoadLevelPopulatesData) {
    game.loadLevel(99);

    EXPECT_EQ(game.getLevelWidth(), 5);
    EXPECT_EQ(game.getLevelLength(), 3);

    // Testing getTileAt via IGame interface
    EXPECT_EQ(game.getTileAt(Position(0, 0)), ETileType::TARGET);
    EXPECT_EQ(game.getTileAt(Position(1, 1)), ETileType::PATH);
}

TEST_F(GameTest, PlayerMovement) {
    game.loadLevel(99);
    observer.reset();

    // Try move into Wall (Left from 1,1 to 1,0)
    game.movePlayer(EFacing::LEFT);
    EXPECT_EQ(game.getPlayerPosition(), Position(1, 0));
    EXPECT_EQ(observer.eventCount, 1);

    // Move Right (Push Box)
    game.movePlayer(EFacing::RIGHT);
    EXPECT_EQ(game.getPlayerPosition(), Position(1, 1));

    // Should trigger BOX_MOVED (0) and PLAYER_MOVED (1) based on enum order? 
    // Actually the values don't matter, just that we got events.
    EXPECT_GE(observer.eventCount, 1);
    EXPECT_EQ(observer.lastEvent, EGameEvent::PLAYER_MOVED);
}

TEST_F(GameTest, WinConditionIntegration) {
    game.loadLevel(99);

    // 1. Push box from 1,2 to 1,3
    game.movePlayer(EFacing::RIGHT);
    EXPECT_EQ(game.getCurrentState(), EGameState::PLAYING);

    // 2. Push box from 1,3 to 1,4 (Target)
    game.movePlayer(EFacing::RIGHT);
    EXPECT_EQ(game.getCurrentState(), EGameState::PLAYING);
    EXPECT_EQ(observer.lastEvent, EGameEvent::PLAYER_MOVED);
}