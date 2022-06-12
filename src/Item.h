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
    Item(ItemType t, float dt);
    ~Item();
public:
    float GetDropTime() const;
    ItemType GetItemType() const;

    void Update(float dt);
    void Render();
};