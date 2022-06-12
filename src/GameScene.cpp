/**
 * @file GameScene.cpp
 */

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
  //delete mapManager;
  nodelay(stdscr, false);
  endwin();
}

// initialise the game window
void GameScene::InitGameWindow()
{
  initscr(); // initialise the screen
  nodelay(stdscr, TRUE);
  keypad(stdscr, true);                  // initialise the keyboard: we can use arrows for directions
  noecho();                              // user input is not displayed on the screen
  curs_set(0);                           // cursor symbol is not not displayed on the screen (Linux)
  getmaxyx(stdscr, maxheight, maxWidth); // define dimensions of game window
  return;
}

void GameScene::ProcessCollision()
{
  int y = snake->GetHead().y;
  int x = snake->GetHead().x;

  char temp = mapManager->data[y][x];

  // mvaddch(2, maxWidth / 5 * 4 + 4, mapManager->data[y][x]);

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
  if (player->GetLengthScore() >= stage->mission[stage->getNowStage()][0] && player->GetGrowScore() >= stage->mission[stage->getNowStage()][1] && player->GetPoisonScore() >= stage->mission[stage->getNowStage()][2] && player->GetGateScore() == stage->mission[stage->getNowStage()][3])
  {
    return true;
  }
  return false;
}

void GameScene::Update(float eTime) {
  if (isClear()) {
    stage->nowStage += 1;
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
      int spriteIndex = mapManager->data[i][j] - '0';
      if (spriteIndex >= 0 && spriteIndex <= 8) {
        mvaddch(i, j, spriteTable[spriteIndex]);
      }
    }
  }

  refresh();
}