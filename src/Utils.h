#pragma once
#include "IScene.h"
#include "Point.h"
#include <chrono>
#include <iostream>

using namespace std;

#define DROP_ITEM_INTERVAL 3.0f
#define DROP_GATE_INTERVAL 10.0f

#define WIDTH 48
#define HEIGHT 24

void Init();
void Update(float dt); //Elapsed Time
void Render();
void Release();
float GetDeltaTime();
float GetDistance(Point p1, Point p2);
void ChangeScene(IScene *p, bool nowSceneErase = true);