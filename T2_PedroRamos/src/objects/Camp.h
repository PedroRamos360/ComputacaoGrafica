#include <stdio.h>
#include <stdlib.h>
#include "../gl_canvas2d.h"
#include "Player.h"
#include <vector>

#define CAMP_HALF_WIDTH 200
#define CAMP_HALF_HEIGHT 300

using namespace std;

class Camp
{
private:
  int *screenWidth, *screenHeight;
  int *mouseX, *mouseY;
  vector<Ball *> balls;
  Player *player;

  void removeBallsOutOfCamp()
  {
    for (int i = 0; i < balls.size(); i++)
    {
      if (balls[i]->x < -CAMP_HALF_WIDTH || balls[i]->x > CAMP_HALF_WIDTH || balls[i]->y < -CAMP_HALF_HEIGHT || balls[i]->y > CAMP_HALF_HEIGHT)
      {
        delete balls[i];
        balls.erase(balls.begin() + i);
      }
    }
  }

  void renderBalls()
  {
    for (int i = 0; i < balls.size(); i++)
    {
      balls[i]->render();
    }
  }

public:
  Camp(int *screenWidth, int *screenHeight, int *mouseX, int *mouseY)
  {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    player = new Player(mouseX, mouseY, screenWidth, screenHeight, CAMP_HALF_WIDTH, CAMP_HALF_HEIGHT, balls);
  }

  void handleMouseClick()
  {
    player->shoot();
  }

  void printBallsPos()
  {
    int i = 0;
  }

  void render()
  {
    CV::translate(*screenWidth / 2, *screenHeight / 2);
    CV::color(0, 0, 0);
    CV::rect(-CAMP_HALF_WIDTH, -CAMP_HALF_HEIGHT, CAMP_HALF_WIDTH, CAMP_HALF_HEIGHT);
    player->render();
    renderBalls();
    removeBallsOutOfCamp();
    printBallsPos();
    CV::translate(0, 0);
  }
};
