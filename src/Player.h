#pragma once

class Player
{
private:
    int lengthScore;
    int growScore;
    int poisonScore;
    int gateScore;
    int totalScore;
public:
    Player();
    ~Player();
public:
    int& GetLengthScore();
    int& GetGrowScore();
    int& GetPoisonScore();
    int& GetGateScore();
    int& GetTotalScore();
};
