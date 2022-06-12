#pragma region Includes

#include "GameScene.h"
#include "GameCoverScene.h"
#include "WaitingScene.h"
#include "Snake.h"
#include "ItemManager.h"
#include "Utils.h"
#include "IObject.h"
#include "ScoreInfo.h"
#include "MapManager.h"
#include "Point.h"
#include "ItemManager.h"
#include "GateManager.h"
#include "UIControl.h"
#include "Stage.h"

#include <unistd.h>
#include <vector>
#include <ncurses.h>

#pragma endregion

using namespace std;

extern Stage *stage;

MapManager *mapManager;
ScoreInfo* scoreInfo;
Snake* snake;

GameScene::GameScene()
{
  srand(time(NULL));

  scoreInfo = new ScoreInfo();

  mapManager = new MapManager();
  mapManager->Load();

  snake = new Snake();
  itemManager = new ItemManager();
  gateManager = new GateManager();

  format = new UIControl();

  InitGameWindow();
  refresh();
}

GameScene::~GameScene()
{
  nodelay(stdscr, false);
  endwin();
}

void GameScene::InitGameWindow()
{
  initscr(); 
  nodelay(stdscr, TRUE);
  keypad(stdscr, true);                  
  noecho();                              
  curs_set(0);                           
  getmaxyx(stdscr, maxheight, maxWidth); 
  return;
}

void GameScene::ProcessCollision() {
  Point pos = snake->GetHead();

  char dataChar = mapManager->GetMapData(pos.y, pos.x);
  if (dataChar == '1' || snake->GetSize() <= 4)
  {
    snake->IsDead() = true;
  }
  else if (dataChar == '5') {
    itemManager->DeleteCollisionData(pos);
    scoreInfo->GetGrowScore() += 1;
    snake->Grow();
  }
  else if (dataChar == '6') {
    itemManager->DeleteCollisionData(pos);
    scoreInfo->GetPoisonScore() += 1;
    snake->Shrink();
  }
  else if (dataChar == '7')
  {
    Point nextGate = gateManager->GetNextGate();
    scoreInfo->GetGateScore() += 1;
    gateManager->IsUsed() = true;
    snake->SetHeadPos(nextGate.y, nextGate.x);
  }
}

bool isClear() {
  int scoreTable[4] = {
    scoreInfo->GetLengthScore(),
    scoreInfo->GetGrowScore(),
    scoreInfo->GetPoisonScore(),
    scoreInfo->GetGateScore()
  };

  bool isClear = true;
  for (int i = 0; i < 4; ++i) {
    if (scoreTable[i] < stage->GetMissionData(i)) {
      isClear = false;
      break;
    }
  }

  return isClear;
}

void GameScene::Update(float eTime) {
  if (isClear()) {
    stage->GetNowStage() += 1;
    if (stage->GetNowStage() > 4) {
      exit(0);
    }
    ChangeScene(new GameCoverScene());
    return;
  }

  scoreInfo->GetLengthScore() = snake->GetSize();
  scoreInfo->GetTotalScore() = stage->GetNowStage();

  snake->Update(eTime);
  if (snake->IsCollision()) {
    ProcessCollision();
  }
  if (snake->IsDead()) {
    ChangeScene(new GameOverScene());
  }

  snake->PushData();
  format->Update(eTime);
  itemManager->Update(eTime);
  gateManager->Update(eTime);
  
  usleep(150000);
}

void GameScene::Render()
{
  format->Render();

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int spriteIndex = mapManager->GetMapData(i, j) - '0';
      if (spriteIndex >= 0 && spriteIndex <= 8) {
        mvaddch(i, j, spriteTable[spriteIndex]);
      }
    }
  }

  refresh();
}