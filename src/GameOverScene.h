#pragma once

#include "IScene.h"

class GameOverScene : public IScene {
public:
    int maxWidth, maxheight;

    GameOverScene();
    ~GameOverScene();

    void Update(float eTime);
    void Render();

    void ClearCentre(float x, float y);

    int UserInput();

    int AskUserToPlayAgain();

    void Load();
};