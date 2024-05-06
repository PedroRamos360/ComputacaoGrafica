#include <stdio.h>
#include <stdlib.h>
#include "../gl_canvas2d.h"
#include "Player.h"
#include <vector>
#include "Grid.h"
#include "ScoreBoard.h"
#include "Gameover.h"

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
  ScoreBoard *scoreBoard;
  bool playerCanShoot = true;
  Vector2 directionLastShoot;
  int playersShotLeft;
  long lastShootTime;
  bool gameover = false;

  void removeBallsOutOfCamp(bool bypass = false)
  {
    for (int i = 0; i < this->balls.size(); i++)
    {
      if ((this->balls[i]->y < this->balls[i]->radius) || bypass)
      {
        delete this->balls[i];
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
    block->decreaseLife();
    Vector2 ballCenter = Vector2(ball->x, ball->y);
    Vector2 blockCenter = Vector2(block->x + block->size / 2, block->y - block->size / 2);
    float overlapX = ball->radius + block->size / 2 - abs(ballCenter.x - blockCenter.x);
    float overlapY = ball->radius + block->size / 2 - abs(ballCenter.y - blockCenter.y);
    if (overlapX < overlapY)
      ball->direction = ball->direction.reflect(Vector2(getSignal(ballCenter.x - blockCenter.x), 0));
    else
      ball->direction = ball->direction.reflect(Vector2(0, getSignal(ballCenter.y - blockCenter.y)));
  }

  void continuousCollisonBallBlock()
  {
    for (auto ball : this->balls)
      for (auto block : grid->getBlocks())
      {
        if (ball->collidesWithBlock(*block))
        {
          onCollide(block, ball);
        }
      }
  }

  void renderBalls()
  {
    for (int i = 0; i < balls.size(); i++)
      balls[i]->render();
  }

  void shootRestOfBalls()
  {
    long deltaEpoch = getEpochTime() - this->lastShootTime;
    if (!this->playerCanShoot && this->playersShotLeft > 0 && deltaEpoch > 100)
    {
      this->playersShotLeft--;
      player->shoot(this->directionLastShoot, true);
      this->lastShootTime = getEpochTime();
    }
  }

  void checkNextLevel(bool bypass = false)
  {
    if ((!this->playerCanShoot && this->balls.size() == 0) || bypass)
    {
      scoreBoard->increaseScore();
      grid->reduceBlocksHeight(scoreBoard->getBallsCount());
      this->playerCanShoot = true;
    }
  }

  void gameLoop()
  {
    continuousCollisonBallBlock();
    player->render();
    grid->render();
    scoreBoard->render();
    renderBalls();
    bounceBalls();
    removeBallsOutOfCamp();
    checkNextLevel();
    shootRestOfBalls();
    this->gameover = grid->checkGameOver();
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
    scoreBoard = new ScoreBoard(screenWidth, screenHeight, CAMP_HALF_WIDTH, CAMP_HALF_HEIGHT);
  }

  void handleMouseClick()
  {
    if (this->playerCanShoot)
    {
      this->playersShotLeft = scoreBoard->getBallsCount();
      this->directionLastShoot = player->getDirection();
      this->playerCanShoot = !player->shoot(this->directionLastShoot);
      this->playersShotLeft--;
      this->lastShootTime = getEpochTime();
    }
  }

  void handleArrowDown()
  {
    removeBallsOutOfCamp(true);
    checkNextLevel(true);
  }

  void render()
  {
    CV::translate(*screenWidth / 2, *screenHeight / 2);
    CV::color(0, 0, 0);
    CV::rect(-CAMP_HALF_WIDTH, -CAMP_HALF_HEIGHT, CAMP_HALF_WIDTH, CAMP_HALF_HEIGHT);
    if (this->gameover)
    {
      Gameover *gameoverScreen = new Gameover(screenHeight, screenWidth, scoreBoard->getBallsCount());
      gameoverScreen->render();
      delete gameoverScreen;
    }
    else
    {
      gameLoop();
    }
    CV::translate(0, 0);
  }
};