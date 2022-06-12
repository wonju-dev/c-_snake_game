#pragma once

#include "IScene.h"

class Stage;
class GameScene;

/*
#include "IScene.h"
#include "Stage.h"
#include "myFunction.h"
#include "GameScene.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
*/

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