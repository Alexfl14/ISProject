#include "pch.h"
#include "Player.h"

TEST(PlayerTest, Initialization) {
    Position startPos(3, 4);
    Player player(startPos); // Assuming constructor takes Position

    EXPECT_EQ(player.getPosition().getRow(), 3);
    EXPECT_EQ(player.getPosition().getCol(), 4);
}

TEST(PlayerTest, MovementUpdatesPosition) {
    Player player(Position(0, 0));
    player.setPosition(Position(1, 1));

    EXPECT_EQ(player.getPosition().getRow(), 1);
    EXPECT_EQ(player.getPosition().getCol(), 1);
}