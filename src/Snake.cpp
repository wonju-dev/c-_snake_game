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

void Snake::PushData()
{
    for (int i = 0; i < entire.size(); ++i) {
        if (i == 0) {
            mapManager->PatchData(entire[i].y, entire[i].x, '3');
        }
        else {
            mapManager->PatchData(entire[i].y, entire[i].x, '4');
        }
    }
}

void Snake::initBody() {
    for (int i = 0; i < 5; ++i) {
        entire.push_back(Point(15 + i, 20));
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

    if (entire.size() <= 3)
    {
        isDead = true;
    }

    if (isDead == false)
    {
        if (direction == 'l')
        {
            entire.insert(entire.begin(), Point(entire[0].x - 1, entire[0].y));
        }
        else if (direction == 'r')
        {
            entire.insert(entire.begin(), Point(entire[0].x + 1, entire[0].y));
        }
        else if (direction == 'u')
        {
            entire.insert(entire.begin(), Point(entire[0].x, entire[0].y - 1));
        }
        else if (direction == 'd')
        {
            entire.insert(entire.begin(), Point(entire[0].x, entire[0].y + 1));
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
    if (mapManager->data[head.y][head.x] != '0')
    {
        return true;
    }
    return false;
}

void Snake::SetHeadPos(int y, int x)
{
    entire[0].x = x;
    entire[0].y = y;
}

void Snake::CutTail()
{
    mapManager->PatchData(entire[entire.size() - 1].y, entire[entire.size() - 1].x, '0');
    entire.pop_back();
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
    return entire.size();
}

Point Snake::GetHead()
{
    return entire[0];
}

Point Snake::GetTail()
{
    return entire[entire.size() - 1];
}

void Snake::Render()
{
}
