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
	int nowStage;
	bool clear;
public:
	Stage(int nextStage = 0);
	~Stage();
public:
	int& GetNowStage();
	const int* GetNowMission() const;
	int const GetMissionData(int index) const;

	void Update(float eTime);

	void Render();
};