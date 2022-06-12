#include <cstdlib>
#include <ctime>
#include <string>
#include "Snake.h"
#include <iostream>
#include "Item.h"
#include "ItemManager.h"
#include "GameScene.h"
#include "Utils.h"
#include "MapManager.h"

extern MapManager *mapManager;
extern Snake* snake;

ItemManager::ItemManager() {
    int maxHeight, maxWidth;
    getmaxyx(stdscr, maxHeight, maxWidth);
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

void ItemManager::DeleteCollisionData(Point pos) {
    itemData.erase(pos);
    mapManager->UpdateData(pos.y, pos.x, '0');
}

void ItemManager::Update(float dt) {
    std::vector<Point> toRemoveList;

    if (dt - lastDropTime > DROP_ITEM_INTERVAL) {
        int randNum = GetRandomNumber(0, 2);
        if (randNum == 0) {
            CreateItem(ItemType::Poision, dt);
        }
        else {
            CreateItem(ItemType::Fruit, dt);
        }
        lastDropTime = dt;
    }

    for (const std::pair<Point, Item>& data : itemData) {
        if (isExceedTime(data.second, dt)) {
            toRemoveList.push_back(data.first);
        }
    }

    for (int i = 0; i < toRemoveList.size(); ++i) {
        itemData.erase(toRemoveList[i]);
        mapManager->UpdateData(toRemoveList[i].y, toRemoveList[i].x, '0');
    }
}

void ItemManager::CreateItem(ItemType type, float dt) {
    Point position;
    while (true) {
        int x = GetRandomNumber(0, WIDTH);
        int y = GetRandomNumber(0, HEIGHT);

        if (mapManager->GetMapData(y, x) == '0') {
            float distFromHead = GetDistance(Point(x, y), snake->GetHead());
            float distFromTail = GetDistance(Point(x, y), snake->GetTail());
            int snakeSize = snake->GetSize();
            int padding = 3;
            if (distFromHead < snakeSize + padding || distFromTail < snakeSize + padding)
                continue;
            
            position = Point(x, y);
            break;
        }
    }

    itemData.insert(std::make_pair(position, Item(type, dt)));
    char idx = (type == ItemType::Fruit) ? '5' : '6';
    mapManager->UpdateData(position.y, position.x, idx);
}
