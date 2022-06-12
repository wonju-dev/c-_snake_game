#include "WaitingScene.h"
#include "GameScene.h"
#include "Utils.h"
#include "Stage.h"
#include <fstream>

Stage *stage;

extern int currentWidth;
extern int currentHeight;

WaitingScene::WaitingScene()
{
    stage = new Stage();
}

WaitingScene::~WaitingScene()
{
}

void WaitingScene::Update(float eTime)
{
    char answer;
    answer = IsUserReady();
    if (answer == 'n')
        exit(0);

    stage->setNowStage(0);

    ChangeScene(new GameScene());
}

void WaitingScene::Render()
{
}

void WaitingScene::ClearCentre(float x, float y)
{
    clear(); // clear the screen if the game is played for the 2nd time
    initscr();
    noecho();
    getmaxyx(stdscr, maxheight, maxWidth);

    getmaxyx(stdscr, currentHeight, currentWidth);

    move((maxheight / y), (maxWidth / x));
}

// receive user confirmation
int WaitingScene::UserInput()
{
    int UserInput = getch();
    refresh();
    endwin();
    clear();

    return UserInput;
}

void WaitingScene::Load()
{
    std::ifstream readFile;
    std::string src = "scene/WaitingScene.txt";

    readFile.open(src);
    int height = 0;

    while (!readFile.eof())
    {
        char temp[120];
        readFile.getline(temp, 120);

        for (int width = 0; width < 62; width++)
        {
            if (temp[width] == '-')
            {
                move(height, width);
                addch('-');
            }

            else if (temp[width] == 'o')
            {
                move(height, width);
                addch(char(219));
            }

            else if (temp[width] == ' ')
            {
                move(height, width);
                addch(' ');
            }
        }

        height++;
    }
}

// print start menu
int WaitingScene::IsUserReady()
{
    ClearCentre(3, 2.5);

    Load();

    move(25, 20);
    printw("Press any key to start");
    move(30, 14);
    return UserInput();
}