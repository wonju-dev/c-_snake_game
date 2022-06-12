#include "GameScene.h"
#include "Stage.h"
#include "Point.h"

Stage::Stage(int nextStage) {
    nowStage = nextStage;
}

Stage::~Stage() {
}

int& Stage::GetNowStage() { 
    return nowStage; 
}

const int* Stage::GetNowMission() const {
    return mission[nowStage]; 
}

int const Stage::GetMissionData(int index) const {
    return GetNowMission()[index];
}

void Stage::Update(float eTime) {
}

void Stage::Render() {
}