#pragma once

#include "IScene.h"

class ItemManager;
class GateManager;
class UIControl;

class GameScene : public IScene {
private:
	const char spriteTable[10] = " -XHBGPO ";
	ItemManager *itemManager;
	GateManager *gateManager;
	UIControl *format;

	int score;
	int maxWidth, maxheight;

	char edgechar;
	bool isChangeScene;
public:
	GameScene();
	~GameScene();
public:

	void InitGameWindow();
	void Update(float eTime);
	void Render();
	void ProcessCollision();
};