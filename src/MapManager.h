#pragma once
#include "IObject.h"
#include "Point.h"
#include "Utils.h"
#include "IScene.h"
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <ctime>

class MapManager : public IObject {
private:
    char mapData[HEIGHT][WIDTH];
    float lastDropTime;
public:
    MapManager();
    ~MapManager();
public:
    void Render();
    void Update(float eTime);

    void* GetData();
    void UpdateData(int y, int x, char newData);

    char GetMapData(int r, int c) const;
    float GetLastDropTime() const;

    void Print();
    void Load();
};