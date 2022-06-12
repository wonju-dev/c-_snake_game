#include "GameScene.h"
#include "Stage.h"
#include "Point.h"

Stage::Stage(int nextStage) {
    nowStage = nextStage;
}

Stage::~Stage() {
}

int Stage::getNowStage() const { 
    return nowStage; 
}

const int* Stage::getNowMission() const {
    return mission[nowStage]; 
}

int const Stage::getMissionData(int index) const {
    return getNowMission()[index];
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