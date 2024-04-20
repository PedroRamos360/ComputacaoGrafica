#include <stdio.h>
#include <stdlib.h>
#include "../gl_canvas2d.h"
#include "Player.h"
#include <vector>
#include "Grid.h"

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
  Grid *grid;

  void removeBallsOutOfCamp()
  {
    for (int i = 0; i < this->balls.size(); i++)
    {
      if (this->balls[i]->y < this->balls[i]->radius)
      {
        delete this->balls[i];
        this->balls.erase(this->balls.begin() + i);
      }
    }
  }

  void bounceBalls()
  {
    for (int i = 0; i < this->balls.size(); i++)
    {
      if (this->balls[i]->x < -CAMP_HALF_WIDTH + balls[i]->radius && this->balls[i]->direction.x < 0)
      {
        this->balls[i]->direction.x *= -1;
      }
      if (this->balls[i]->x > CAMP_HALF_WIDTH - balls[i]->radius && this->balls[i]->direction.x > 0)
      {
        this->balls[i]->direction.x *= -1;
      }
      if (this->balls[i]->y > 2 * CAMP_HALF_HEIGHT - balls[i]->radius && this->balls[i]->direction.y > 0)
      {
        this->balls[i]->direction.y *= -1;
      }
    }
  }

  void checkColisionWithBlocks()
  {
    for (auto block : grid->getBlocks())
    {
      for (auto ball : this->balls)
      {
        float dx = ball->x - std::max(block->x, std::min(ball->x, block->x + block->size));
        float dy = ball->y - std::max(block->y, std::min(ball->y, block->y + block->size));
        bool collision = (dx * dx + dy * dy) < (ball->radius * ball->radius);
        if (collision)
        {
          printf("Colidiu");
          ball->direction = ball->direction * -1;
        }
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
    grid = new Grid(CAMP_HALF_WIDTH, CAMP_HALF_HEIGHT, screenWidth, screenHeight);
  }

  void handleMouseClick()
  {
    player->shoot();
  }

  void render()
  {
    CV::translate(*screenWidth / 2, *screenHeight / 2);
    CV::color(0, 0, 0);
    CV::rect(-CAMP_HALF_WIDTH, -CAMP_HALF_HEIGHT, CAMP_HALF_WIDTH, CAMP_HALF_HEIGHT);
    player->render();
    grid->render();
    renderBalls();
    checkColisionWithBlocks();
    bounceBalls();
    removeBallsOutOfCamp();
    CV::translate(0, 0);
  }
};
