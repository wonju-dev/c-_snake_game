#include <cstdlib>
#include <ctime>
#include <string>
#include "Snake.h"
#include "Item.h"
#include "ItemManager.h"
#include "GameScene.h"
#include "MapManager.h"

extern MapManager *mapManager;

ItemManager::ItemManager() {
    getmaxyx(stdscr, maxheight, maxWidth);
}

ItemManager::~ItemManager() {
}

void ItemManager::Render() {
}

bool isExceedTime(Item item, float dt) {
    if (dt - item.GetDropTime() > 10) {
        return true;
    }
    return false;
}

void ItemManager::DeleteCollisionData(int y, int x) {
    int target;

    for (int i = 0; i < data.size(); ++i) {
        if (data[i].position.x == x && data[i].position.y == y) {
            target = i;
        }
    }
    data.erase(data.begin() + target);
}

void ItemManager::Update(float dt) {
    int *temp = new int[data.size()];
    std::vector<Item>::iterator iter;

    if (dt - lastDropTime > DROP_ITEM_INTERVAL && data.size() <= 3) {
        int randNum = rand() % 2;
        if (randNum == 0)
        {
            CreateItem(ItemType::Poision, dt);
        }
        else
        {
            CreateItem(ItemType::Fruit, dt);
        }
        PushData();
        lastDropTime = dt;
    }

    for (int i = 0; i < data.size(); ++i) {
        if (isExceedTime(data[i], dt)) {
            temp[i] = 1;
        }
        else {
            temp[i] = 0;
        }
    }

    for (int i = data.size() - 1; i >= 0; --i) {
        if (temp[i] == 1) {
            mapManager->UpdateData(data[i].position.y, data[i].position.x, '0');
            data.erase(data.begin() + i);
        }
    }

    delete[] temp;

    PushData();
}

void ItemManager::CreateItem(ItemType type, float dt) {
    data.push_back(Item(type, dt));
}

void ItemManager::PushData() {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].GetItemType() == ItemType::Fruit) {
            mapManager->UpdateData(data[i].position.y, data[i].position.x, '5');
        }
        else if (data[i].GetItemType() == ItemType::Poision) {
            mapManager->UpdateData(data[i].position.y, data[i].position.x, '6');
        }
    }
}
