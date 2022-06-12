#include "Item.h"
#include "Point.h"
#include "Utils.h"
#include "MapManager.h"
#include "GameScene.h"
#include "Snake.h"

extern MapManager* mapManager;

Item::Item(ItemType t, float dt) : type(t), dropTime(dt)
{ }

float Item::GetDropTime() const {
    return dropTime;
}

ItemType Item::GetItemType() const {
    return type;
}

Item::~Item() {
}

void Item::Update(float dt) {
}

void Item::Render() {
}