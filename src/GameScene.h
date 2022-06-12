#pragma once

#include "IScene.h"
#include "ItemManager.h"
#include "GateManager.h"
#include "Format.h"

class GameScene : public IScene {
private:
	const char spriteTable[10] = " -XHBGPO ";
public:
	int score;
	int maxWidth, maxheight;

	char edgechar;

	GameScene();
	~GameScene();

	ItemManager *itemManager;
	GateManager *gateManager;

	Format *format;

	bool isChangeScene;

	void InitGameWindow();
	void Update(float eTime);
	void Render();
	void ProcessCollision();
};