#include <cstdlib>
#include <ctime>
#include <string>
#include "Snake.h"
#include "GateManager.h"
#include "GameScene.h"
#include "MapManager.h"

extern MapManager *mapManager;
extern Snake *snake;

Point nextPos;

Point GateManager::getRandPosition()
{
    Point temp;
    while (true) {
        int x = GetRandomNumber(0, WIDTH);
        int y = GetRandomNumber(0, HEIGHT);
        if (mapManager->GetMapData(y, x) == '1') {
            temp.x = x;
            temp.y = y;
            break;
        }
    }
    return temp;
}

GateManager::GateManager() {
}

GateManager::~GateManager() {
}

void GateManager::Render() {
}

Point GateManager::GetNextGate() {
    int target = 9;

    for (int i = 0; i < data.size(); ++i) {
        if (data[i].x == snake->GetHead().x && data[i].y == snake->GetHead().y) {
            target = i;
        }
    }

    if (target == 0)
    {
        target = 1;
    }
    else
    {
        target = 0;
    }

    int tempPosX = data[target].x;
    int tempPosY = data[target].y;

    bool possibleLeft = false;
    bool possibleRight = false;
    bool possibleUp = false;
    bool possibleDown = false;

    char direction = snake->GetDirection();

    if (mapManager->GetMapData(tempPosY + 1, tempPosX) == '0') {
        possibleDown = true;
    }
    if (mapManager->GetMapData(tempPosY, tempPosX + 1) == '0') {
        possibleRight = true;
    }
    if (mapManager->GetMapData(tempPosY - 1, tempPosX) == '0') {
        possibleUp = true;
    }
    if (mapManager->GetMapData(tempPosY, tempPosX - 1) == '0') {
        possibleLeft = true;
    }

    if (possibleLeft && direction == 'l') {
        tempPosX -= 1;
    }
    else if (possibleRight && direction == 'r') {
        tempPosX += 1;
    }
    else if (possibleUp && direction == 'u') {
        tempPosY -= 1;
    }
    else if (possibleDown && direction == 'd') {
        tempPosY += 1;
    }

    else if (direction == 'u' || direction == 'd') {
        if (possibleLeft) {
            tempPosX -= 1;
            snake->SetDirection('l');
        }
        else if (possibleRight) {
            tempPosX += 1;
            snake->SetDirection('r');
        }
        else if (possibleUp) {
            tempPosY -= 1;
            snake->SetDirection('u');
        }
        else if (possibleDown) {
            tempPosY += 1;
            snake->SetDirection('d');
        }
    }

    else if (direction == 'l' || direction == 'r') {
        if (possibleDown) {
            tempPosY += 1;
            snake->SetDirection('d');
        }
        else if (possibleUp) {
            tempPosY -= 1;
            snake->SetDirection('u');
        }
        else if (possibleLeft) {
            tempPosX -= 1;
            snake->SetDirection('l');
        }
        else if (possibleRight) {
            tempPosX += 1;
            snake->SetDirection('r');
        }
    }

    nextPos.x = tempPosX;
    nextPos.y = tempPosY;

    return nextPos;
}

void GateManager::Update(float dt)
{
    int *temp = new int[data.size()];
    vector<Point>::iterator iter;

    if (isEntering) {
        Point tail = snake->GetTail();
        if (nextPos.x == tail.x && nextPos.y == tail.y) {
            isRemove = true;
        }

        if (isRemove == true) {
            for (int i = data.size() - 1; i >= 0; --i) {
                mapManager->UpdateData(data[i].y, data[i].x, '1');
                data.pop_back();
            }
            isCreated = false;
            isRemove = false;
            isEntering = false;
            lastDropTime = dt;
        }
    }
    else if (isCreated && !isEntering && dt - lastDropTime > DROP_GATE_INTERVAL) {
        for (int i = data.size() - 1; i >= 0; i--) {
            mapManager->UpdateData(data[i].y, data[i].x, '1');
            data.pop_back();
        }
        isCreated = false;
    }

    PushData();

    if (dt - lastDropTime > DROP_GATE_INTERVAL && !isEntering && snake->GetSize() >= 4) {
        if (!isCreated)
        {
            PositionGate();
            lastDropTime = dt;
            isCreated = true;
        }
    }

    delete[] temp;
}

void GateManager::PositionGate() {
    Point temp = getRandPosition();
    data.push_back(temp);
    PushData();
    temp = getRandPosition();
    data.push_back(temp);
    PushData();
}

void GateManager::PushData() {
    for (int i = 0; i < data.size(); i++) {
        mapManager->UpdateData(data[i].y, data[i].x, '7');
    }
}

bool& GateManager::IsUsed() {
    return isUsed;
}