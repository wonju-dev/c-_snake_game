#include "GameScene.h"
#include "Stage.h"
#include "Point.h"

Stage::Stage(int nextStage) {
    nowStage = nextStage;
}

Stage::~Stage() {
}

int Stage::getNowStage() { 
    return nowStage; 
}

int* Stage::getNowMission() {
    return mission[nowStage]; 
}

void Stage::setNowStage(int nowStage) { 
    this->nowStage = nowStage; 
}

void Stage::Update(float eTime)
{
}

void Stage::Render()
{
}