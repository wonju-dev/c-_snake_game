#pragma once

class ScoreInfo {
private:
    int lengthScore;
    int growScore;
    int poisonScore;
    int gateScore;
    int totalScore;
public:
    ScoreInfo();
    ~ScoreInfo();
public:
    int& GetLengthScore();
    int& GetGrowScore();
    int& GetPoisonScore();
    int& GetGateScore();
    int& GetTotalScore();
};
