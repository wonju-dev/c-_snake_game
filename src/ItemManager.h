#pragma once

#include "Item.h"
#include "IObject.h"
#include <vector>
#include <string>
#include <map>

class ItemManager : public IObject {
private:
    std::vector<Item> data;
public:
    int maxheight, maxWidth;
    float lastDropTime = 0;

    ItemManager();
    ~ItemManager();

    void Render();
    void Update(float dt);
    void CreateItem(ItemType type, float dt);
    void DeleteCollisionData(int y, int x);

    void PushData();
};