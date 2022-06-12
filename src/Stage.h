#pragma once
#include "IObject.h"

class Stage : public IObject
{
public:
	int nowStage;
	bool clear;

	int mission[3][4] = {
		{6, 1, 1, 1},
		{6, 2, 2, 2},
		{6, 2, 3, 3},
	};

	Stage(int nextStage = 0);
	~Stage();

	int getNowStage();

	int *getNowMission();

	void setNowStage(int nowStage);

	void Update(float eTime);

	void Render();
};