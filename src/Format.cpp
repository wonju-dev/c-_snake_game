#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include "ScoreInfo.h"
#include "Stage.h"
#include "Format.h"

extern ScoreInfo *player;
extern Stage *stage;

Format::Format() {
    gameStartTime = -1;
    gameTime = -1;
    getmaxyx(stdscr, maxHeight, maxWidth);
}
Format::~Format() {
}

void Format::Update(float dt)
{
    DrawTime(dt);
}

void Format::Render() {
    DrawScore();
    DrawMission();
}

void Format::DrawScore() {
    move(7, maxWidth / 5 * 4 + 4);
    printw("< S C O R E >");

    for (int i = 0; i < 26; ++i)
    {
        move(8, maxWidth / 5 * 4 - 3 + i);
        addch('-');
    }

    int digit = 100, totalScore = player->GetTotalScore();

    for (int i = 0; i < 3; ++i) {
        int digitScore;
        std::string s = "00000";

        digitScore = totalScore / digit;
        totalScore %= digit;

        for (int j = 0; j < 5; ++j) {
            move(11 + j, maxWidth / 5 * 4 - 2 + 4 + i * 6);
            printw("%s", score[digitScore][j]);
        }
        digit /= 10;
    }

    for (int i = 0; i < 26; ++i) {
        move(18, maxWidth / 5 * 4 - 3 + i);
        addch('-');
    }
}

void Format::DrawTime(float dt)
{
    int digit = 10;

    if (gameStartTime == -1)
    {
        gameStartTime = dt;
    }

    gameTime = dt - gameStartTime;
    digitTime = (int)(60 - gameTime);

    for (int j = 0; j < 5; ++j) {
        move(1 + j, maxWidth / 5 * 4 - 2 + 2);
        printw("%s", score[0][j]);
    }

    for (int i = 0; i < 26; ++i) {
        move(6, maxWidth / 5 * 4 - 3 + i);
        addch('-');
        move(0, maxWidth / 5 * 4 - 3 + i);
        addch('-');
    }

    move(2, maxWidth / 5 * 4 - 2 + 8);
    addch(char(219));

    move(4, maxWidth / 5 * 4 - 2 + 8);
    addch(char(219));

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            move(1 + j, maxWidth / 5 * 4 - 2 + 4 + (i + 1) * 6);
            printw("%s", score[digitTime / digit][j]);
        }
        digitTime = digitTime % digit;
        digit /= 10;
    }
}

char Format::Complete(int present, int goal) {
    if (present >= goal)
        return 'V';
    else
        return ' ';
}

void Format::DrawMission() {
    const int* nowMission = stage->getNowMission();

    move(maxHeight / 2, maxWidth / 5 * 4 + 1);
    printw("< M I S S I O N >");

    for (int i = 0; i < 26; ++i)
    {
        move(maxHeight / 2 + 1, maxWidth / 5 * 4 - 3 + i);
        addch('-');
    }

    move(22, maxWidth / 5 * 4 + 4);
    printw("Length : %d/%d (%c)", player->GetLengthScore(), nowMission[0], Complete(player->GetLengthScore(), nowMission[0]));

    move(24, maxWidth / 5 * 4 + 4);
    printw("Fruit : %d/%d (%c)", player->GetGrowScore(), nowMission[1], Complete(player->GetGrowScore(), nowMission[1]));

    move(26, maxWidth / 5 * 4 + 4);
    printw("Poison : %d/%d (%c)", player->GetPoisonScore(), nowMission[2], Complete(player->GetPoisonScore(), nowMission[2]));

    move(28, maxWidth / 5 * 4 + 4);
    printw("Gate : %d/%d (%c)", player->GetGateScore(), nowMission[3], Complete(player->GetGateScore(), nowMission[3]));

    for (int i = 0; i < 26; ++i)
    {
        move(30, maxWidth / 5 * 4 - 3 + i);
        addch('-');
    }
}