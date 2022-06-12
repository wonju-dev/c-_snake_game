#pragma once
#include <ncurses.h>
#include <vector>
#include "Point.h"
#include "Utils.h"
#include "GameOverScene.h"
#include "IScene.h"
#include "IObject.h"

class Snake : public IObject {
private:
	bool isDead = false;
	char partchar, direction;
	int choiceCount;
	int select;
	int maxWidth, maxheight;
	bool isGrow = false;
	bool isShrink = false;
public:
	Snake();
	~Snake();
public:
	std::vector<Point> entire;
	
	void Update(float eTime);

	void PushData();

	void SetDirection(char ch);

	bool IsCollision();

	void Grow();
	void Shrink();

	bool& IsDead();
	int GetDirection() const;

	Point GetHead();
	Point GetTail();
	int GetSize();

	void SetHeadPos(int y, int x);

	void CutTail();

	void Render();
	void initBody();

	void EatItem(bool fruit, bool poison);
};