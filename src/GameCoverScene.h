#pragma once
#include "IScene.h"

class GameCoverScene : public IScene {
public:
    GameCoverScene();
    ~GameCoverScene();
public:
    void Update(float eTime);
    void Render();
};