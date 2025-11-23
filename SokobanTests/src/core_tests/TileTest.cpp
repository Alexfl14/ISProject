#include "pch.h"
#include "Tile.h"
#include "enums/ETileType.h"

TEST(TileTest, DefaultConstructorIsPath) {
    Tile t;
    EXPECT_EQ(t.getTileType(), ETileType::PATH);
}