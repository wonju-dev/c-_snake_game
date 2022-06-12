#pragma once

class Item;
#include "IObject.h"
#include <vector>
#include <string>

class ItemManager : public IObject {
public:
    int maxheight, maxWidth;

    std::vector<Item> data;

    float lastDropTime = 0;

    ItemManager();
    ~ItemManager();

    void Render();
    void Update(float dt);
    void PositionItem(std::string check, float dt);
    void DeleteCollisionData(int y, int x);

    void PushData();
};