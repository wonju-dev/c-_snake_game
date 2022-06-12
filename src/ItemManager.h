#pragma once

class Item;
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
    void PositionItem(std::string check, float dt);
    void DeleteCollisionData(int y, int x);

    void PushData();
};