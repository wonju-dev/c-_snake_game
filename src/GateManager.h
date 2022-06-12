#pragma once

#include "IObject.h"
#include "Point.h"
#include <vector>

class GateManager : public IObject {
public:
    std::vector<Point> data;
    bool isUsed = true;
    bool isRemove = false;
    bool isCreated = false;
    bool isEntering = false;
    float lastDropTime = 0;
public:
    GateManager();
    ~GateManager();
public:
    Point getRandPosition();

    void Render();
    Point GetNextGate();
    void Update(float eTime);
    void PositionGate();
    void DeleteCollisionData(int y, int x);

    void PushData();
};