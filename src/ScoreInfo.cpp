#include "ScoreInfo.h"

ScoreInfo::ScoreInfo() {
    lengthScore = 0;
    growScore = 0;
    poisonScore = 0;
    gateScore = 0;
    totalScore = 0;
}
ScoreInfo::~ScoreInfo() {}

int& ScoreInfo::GetLengthScore() {
    return lengthScore;
}
int& ScoreInfo::GetGrowScore() {
    return growScore;
}
int& ScoreInfo::GetPoisonScore() {
    return poisonScore;
}
int& ScoreInfo::GetGateScore() {
    return gateScore;
}
int& ScoreInfo::GetTotalScore() {
    return totalScore;
}