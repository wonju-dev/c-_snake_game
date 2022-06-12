#pragma once

#include "Item.h"
#include "IObject.h"
#include <vector>
#include <string>
#include <map>

class ItemManager : public IObject {
private:
    std::map<Point, Item> itemData;
    float lastDropTime;
public:
    ItemManager();
    ~ItemManager();
public:
    void Render();
    void Update(float dt);
    void CreateItem(ItemType type, float dt);
    void DeleteCollisionData(Point pos);
};