#pragma once

#include "IScene.h"

class GameOverScene : public IScene {
public:
    GameOverScene();
    ~GameOverScene();
public:
    void Update(float eTime);
    void Render();

    void ClearCentre(float x, float y);

    int UserInput();

    int AskUserToPlayAgain();

    void Load();
};