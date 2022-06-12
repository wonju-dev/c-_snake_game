#pragma once
#include "IScene.h"
#include "Point.h"
#include <chrono>
#include <iostream>

#define DROP_ITEM_INTERVAL 3.0f
#define DROP_GATE_INTERVAL 10.0f

#define WIDTH 62
#define HEIGHT 32

using namespace std;

void Init();
void Update(float dt); //Elapsed Time
void Render();
void Release();
float GetDeltaTime();
float GetDistance(Point p1, Point p2);
void ChangeScene(IScene *p, bool nowSceneErase = true);