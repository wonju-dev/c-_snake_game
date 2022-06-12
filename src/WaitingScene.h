#pragma once

#include "IScene.h"

class WaitingScene : public IScene
{
public:
	int maxWidth, maxheight;

	WaitingScene();
	~WaitingScene();

	void Update(float eTime);
	void Render();

	void Load();
	void ClearCentre(float x, float y);
	int UserInput();
	int IsUserReady();
};