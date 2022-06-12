#pragma once

#include "Point.h"
#include "IObject.h"
#include <string>

enum class ItemType {
    None,
    Poision,
    Fruit
};

class Item : public IObject {
private:
    float dropTime;
    ItemType type = ItemType::None;
public:
    float GetDropTime() const;
    ItemType GetItemType() const;

    Item(ItemType t, float dt);
    ~Item();

    Point position;
    Point getRandPosition();

    void Update(float dt);
    void Render();
};