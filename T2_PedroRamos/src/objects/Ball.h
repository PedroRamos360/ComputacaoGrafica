#include "../Vector2.h"
#include "../gl_canvas2d.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include "Block.h"

using namespace std;

class Ball
{
private:
  float speed = 7;
  int *screenWidth, *screenHeight;
  long lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  int campHalfWidth;
  int campHalfHeight;

  void move()
  {
    long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    long dt = now - lastTime;
    x += direction.x * speed * dt / 20;
    y += direction.y * speed * dt / 20;
    lastTime = now;
  }

public:
  int radius = 5;
  float x = 0, y = radius;
  Vector2 direction;
  string lastCollidedBlockId = "";
  Ball(Vector2 direction, int *screenWidth, int *screenHeight, int campHalfWidth, int campHalfHeight)
  {
    this->direction = direction;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->campHalfWidth = campHalfWidth;
    this->campHalfHeight = campHalfHeight;
  }

  void render()
  {
    CV::translate(*screenWidth / 2, *screenHeight / 2 - this->campHalfHeight);
    CV::color(0, 0, 0);
    CV::circleFill(x, y, radius, 50);
    this->move();
    CV::translate(0, 0);
  }

  bool collidesWithBlock(const Block &block)
  {
    float nextX = x + direction.x * speed;
    float nextY = y + direction.y * speed;
    if (nextX + radius >= block.x && nextX - radius <= block.x + block.size &&
        nextY + radius >= block.y - block.size && nextY - radius <= block.y)
    {
      return true;
    }
    return false;
  }
};
