#include "Utils.h"
#include "WaitingScene.h"
#include <cmath>
#include <random>
#include <chrono>

IScene *nowScene;
bool lkey[256], rkey[256];

int currentWidth;
int currentHeight;

std::chrono::steady_clock::time_point startTime;

void Init() {
	startTime = std::chrono::steady_clock::now();
	nowScene = new WaitingScene();
}

void Update(float eTime)
{
	nowScene->Update(eTime);
}

void Render()
{
	nowScene->Render();
}

void Release()
{
	delete nowScene;
}

float GetDeltaTime()
{
	auto endTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed_seconds = endTime - startTime;
	float eTime = (float)elapsed_seconds.count();
	return eTime;
}

float GetDistance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void ChangeScene(IScene *p, bool nowSceneErase) {
	if (nowSceneErase)
		delete nowScene;
	nowScene = p;
}

int GetRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}