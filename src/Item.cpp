#include "Item.h"
#include "Point.h"
#include "Utils.h"
#include "MapManager.h"
#include "GameScene.h"
#include "Snake.h"

extern MapManager* mapManager;
extern Snake* snake;

Point Item::getRandPosition()
{
    Point temp;

    while (true) {
        int x = rand() % (WIDTH);
        int y = rand() % (HEIGHT);

        if (mapManager->data[y][x] == '0') {
            float distFromHead = GetDistance(Point(x, y), snake->GetHead());
            float distFromTail = GetDistance(Point(x, y), snake->GetTail());
            int snakeSize = snake->GetSize();
            if (distFromHead < snakeSize + 2 || distFromTail < snakeSize + 2)
                continue;
            
            temp.x = x;
            temp.y = y;
            break;
        }
    }
    return temp;
}

Item::Item(std::string t, float dt) : type(t), dropTime(dt) {
    Point temp = getRandPosition();
    position.x = temp.x;
    position.y = temp.y;
}

Item::~Item() {
}

void Item::Update(float dt) {
}

void Item::Render() {
}