#include "pch.h"
#include "GameObject.h"
#include "interfaces/IGameObject.h"

// Concrete class for testing abstract GameObject
class TestObject : public GameObject {
public:
    using GameObject::GameObject;
};

TEST(GameObjectTest, DefaultConstructorZeroesPosition) {
    TestObject obj;
    // Checks that it defaults to 0,0
    EXPECT_EQ(obj.getPosition().getRow(), 0);
    EXPECT_EQ(obj.getPosition().getCol(), 0);
}

TEST(GameObjectTest, SetPositionUpdatesValue) {
    TestObject obj;
    Position p(10, 20);
    obj.setPosition(p);

    EXPECT_EQ(obj.getPosition(), p);
}