#include "MapManager.h"
#include "Utils.h"
#include "Stage.h"
#include <vector>
#include <fstream>

extern Stage *stage;

MapManager::MapManager() {
    lastDropTime = 0;
}

void MapManager::Load()
{
    std::ifstream readFile;
    string src = "map/map" + std::to_string(stage->GetNowStage() + 1) + ".txt";

    readFile.open(src);
    int height = 0;

    while (!readFile.eof())
    {
        char temp[120];
        readFile.getline(temp, 120);

        for (int i = 0; i < WIDTH; i++)
        {
            mapData[height][i] = temp[i];
        }

        height++;
    }
}

void *MapManager::GetData()
{
    return mapData;
}

void MapManager::UpdateData(int y, int x, char newData) {
    mapData[y][x] = newData;
}

char MapManager::GetMapData(int r, int c) const {
    return mapData[r][c];
}

float MapManager::GetLastDropTime() const {
    return lastDropTime;
}

MapManager::~MapManager()
{
}

void MapManager::Render()
{
}

void MapManager::Update(float eTime)
{
}
