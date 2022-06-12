#include "GameScene.h"
#include "GameCoverScene.h"
#include "WaitingScene.h"
#include "Snake.h"
#include "ItemManager.h"
#include "Utils.h"
#include "IObject.h"
#include "Player.h"
#include "MapManager.h"
#include "Point.h"
#include "Stage.h"

#include <unistd.h>
#include <vector>
#include <ncurses.h>

using namespace std;

extern Stage *stage;

MapManager *mapManager;
Player* player;
Snake* snake;

GameScene::GameScene()
{
  srand(time(NULL));

  player = new Player();

  mapManager = new MapManager();
  mapManager->Load();

  snake = new Snake();
  itemManager = new ItemManager();
  gateManager = new GateManager();

  format = new Format();

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

void GameScene::ProcessCollision()
{
  int y = snake->GetHead().y;
  int x = snake->GetHead().x;

  char temp = mapManager->GetMapData(y, x);

  if (temp == '1' || snake->entire.size() <= 4)
  {
    snake->IsDead() = true;
  }
  else if (temp == '5')
  {
    itemManager->DeleteCollisionData(y, x);
    player->GetGrowScore() += 1;
    snake->Grow();
  }
  else if (temp == '6')
  {
    itemManager->DeleteCollisionData(y, x);
    player->GetPoisonScore() += 1;
    snake->Shrink();
  }
  else if (temp == '7')
  {
    Point nextGate = gateManager->GetNextGate();
    player->GetGateScore() += 1;
    gateManager->isUsed = true;
    snake->SetHeadPos(nextGate.y, nextGate.x);
  }
}

bool isClear() {
  int scoreTable[4] = {
    player->GetLengthScore(),
    player->GetGrowScore(),
    player->GetPoisonScore(),
    player->GetGateScore()
  };

  bool isClear = true;
  for (int i = 0; i < 4; ++i) {
    if (scoreTable[i] < stage->getMissionData(i)) {
      isClear = false;
      break;
    }
  }

  return isClear;
}

void GameScene::Update(float eTime) {
  if (isClear()) {
    ++stage->nowStage;
    if (stage->nowStage > 4) {
      exit(0);
    }
    ChangeScene(new GameCoverScene());
    return;
  }

  player->GetLengthScore() = snake->entire.size();
  player->GetTotalScore() = stage->nowStage;

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