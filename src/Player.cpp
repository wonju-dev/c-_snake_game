#include "Player.h"

Player::Player() {
    lengthScore = 0;
    growScore = 0;
    poisonScore = 0;
    gateScore = 0;
    totalScore = 0;
}
Player::~Player() {}

int& Player::GetLengthScore() {
    return lengthScore;
}
int& Player::GetGrowScore() {
    return growScore;
}
int& Player::GetPoisonScore() {
    return poisonScore;
}
int& Player::GetGateScore() {
    return gateScore;
}
int& Player::GetTotalScore() {
    return totalScore;
}