#pragma once
#include "IObject.h"

class Stage : public IObject {
private:
	int const mission[4][4] = {
		{6, 1, 1, 1},
		{6, 2, 2, 2},
		{7, 2, 3, 3},
		{8, 3, 3, 3},
	};
public:
	int nowStage;
	bool clear;

	Stage(int nextStage = 0);
	~Stage();

	int getNowStage() const;
	const int* getNowMission() const;
	int const getMissionData(int index) const;

	void setNowStage(int nowStage);

	void Update(float eTime);

	void Render();
};