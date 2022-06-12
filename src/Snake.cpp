#include "Point.h"
#include "Utils.h"
#include "GameOverScene.h"
#include "IScene.h"
#include "Snake.h"
#include "MapManager.h"

extern MapManager *mapManager;

Snake::Snake()
{
    direction = 'l';
    partchar = '*';
    getmaxyx(stdscr, maxheight, maxWidth);
    initBody();
}

Snake::~Snake() {
}

void Snake::PushData() {
    for (int i = 0; i < snakeVector.size(); ++i) {
        if (i == 0) {
            mapManager->UpdateData(snakeVector[i].y, snakeVector[i].x, '3');
        }
        else {
            mapManager->UpdateData(snakeVector[i].y, snakeVector[i].x, '4');
        }
    }
}

void Snake::initBody() {
    for (int i = 0; i < 5; ++i) {
        snakeVector.push_back(Point(15 + i, 20));
    }
}

void Snake::SetDirection(char ch) {
    direction = ch;
}

void Snake::Update(float eTime) {
    int KeyPressed;

    KeyPressed = getch();
    switch (KeyPressed)
    {
    case KEY_LEFT:
        if (direction != 'r') {
            direction = 'l';
        }
        else
            isDead = true;
        break;
    case KEY_RIGHT:
        if (direction != 'l') {
            direction = 'r';
        }
        else
            isDead = true;
        break;
    case KEY_UP:
        if (direction != 'd') {
            direction = 'u';
        }
        else
            isDead = true;
        break;
    case KEY_DOWN:
        if (direction != 'u')
        {
            direction = 'd';
        }
        else
            isDead = true;
        break;
    }

    if (snakeVector.size() <= 3)
    {
        isDead = true;
    }

    if (isDead == false)
    {
        if (direction == 'l')
        {
            snakeVector.insert(snakeVector.begin(), Point(snakeVector[0].x - 1, snakeVector[0].y));
        }
        else if (direction == 'r')
        {
            snakeVector.insert(snakeVector.begin(), Point(snakeVector[0].x + 1, snakeVector[0].y));
        }
        else if (direction == 'u')
        {
            snakeVector.insert(snakeVector.begin(), Point(snakeVector[0].x, snakeVector[0].y - 1));
        }
        else if (direction == 'd')
        {
            snakeVector.insert(snakeVector.begin(), Point(snakeVector[0].x, snakeVector[0].y + 1));
        }
        if (isGrow == false)
        {
            CutTail();
        }
        else
        {
            isGrow = false;
        }
    }
}

bool Snake::IsCollision()
{
    Point head = GetHead();
    if (mapManager->GetMapData(head.y, head.x) != '0')
    {
        return true;
    }
    return false;
}

void Snake::SetHeadPos(int y, int x)
{
    snakeVector[0].x = x;
    snakeVector[0].y = y;
}

void Snake::CutTail()
{
    mapManager->UpdateData(snakeVector[snakeVector.size() - 1].y, snakeVector[snakeVector.size() - 1].x, '0');
    snakeVector.pop_back();
}

void Snake::Grow()
{
    isGrow = true;
}

void Snake::Shrink()
{
    isShrink = true;
    CutTail();
}

bool& Snake::IsDead() {
    return isDead;
}

int Snake::GetDirection() const {
    return direction;
}

int Snake::GetSize() {
    return snakeVector.size();
}

Point Snake::GetHead()
{
    return snakeVector[0];
}

Point Snake::GetTail()
{
    return snakeVector[snakeVector.size() - 1];
}

void Snake::Render()
{
}
