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

  float getSignal(float value)
  {
    if (value > 0)
      return 1;
    if (value < 0)
      return -1;
    return 0;
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

  void onCollide(Block *block, Ball *ball)
  {
    if (block->getBlockId() != ball->lastCollidedBlockId)
    {
      ball->lastCollidedBlockId = block->getBlockId();
      block->decreaseLife();
    }
  }

  void checkCollisionWithBlocks()
  {
    for (auto ball : this->balls)
      for (auto block : grid->getBlocks())
      {
        Vector2 ballCenter = Vector2(ball->x, ball->y);
        Vector2 blockCenter = Vector2(block->x + block->size / 2, block->y - block->size / 2);
        bool collidedX = ball->x + ball->radius > block->x && ball->x - ball->radius < block->x + block->size;
        bool collidedY = ball->y + ball->radius > block->y - block->size && ball->y - ball->radius < block->y;
        float overlapX = ball->radius + block->size / 2 - abs(ballCenter.x - blockCenter.x);
        float overlapY = ball->radius + block->size / 2 - abs(ballCenter.y - blockCenter.y);
        bool collision = overlapX > 0 && overlapY > 0;
        if (collidedX && collidedY && ball->lastCollidedBlockId == "")
        {
          if (overlapX < overlapY)
          {
            if (ballCenter.x < blockCenter.x)
            {
              ball->direction = ball->direction.reflect(Vector2(-1, 0));
              onCollide(block, ball);
            }
            else
            {
              ball->direction = ball->direction.reflect(Vector2(1, 0));
              onCollide(block, ball);
            }
          }
          else
          {
            if (ballCenter.y < blockCenter.y)
            {
              ball->direction = ball->direction.reflect(Vector2(0, -1));
              onCollide(block, ball);
            }
            else
            {
              ball->direction = ball->direction.reflect(Vector2(0, 1));
              onCollide(block, ball);
            }
          }
        }
        else if (!collision)
        {
          ball->lastCollidedBlockId = "";
        }
      }
  }

  void renderBalls()
  {
    for (int i = 0; i < balls.size(); i++)
      balls[i]->render();
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
    checkCollisionWithBlocks();
    player->render();
    grid->render();
    renderBalls();
    bounceBalls();
    removeBallsOutOfCamp();
    CV::translate(0, 0);
  }
};