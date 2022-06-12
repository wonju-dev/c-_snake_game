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
public:
    float dropTime = 0;
    ItemType type = ItemType::None;

    Item(ItemType t, float eTime);
    ~Item();

    Point position;
    Point getRandPosition();

    void Update(float eTime);
    void Render();
};