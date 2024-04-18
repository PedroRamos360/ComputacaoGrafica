#include "../Vector2.h"
#include "../gl_canvas2d.h"
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

class Ball
{
private:
  int radius = 10;
  Vector2 direction;
  int speed = 5;
  int *screenWidth, *screenHeight;
  long lastTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  int campHalfWidth;
  int campHalfHeight;

  void move()
  {
    long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    x += direction.x * speed * (now - lastTime) /10;
    y += direction.y * speed * (now - lastTime) /10;
    lastTime = now;
  }

public:
  int x = 0, y = 0;
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
    printf("time: %d\n", time(0));
    CV::translate(*screenWidth / 2, *screenHeight / 2 - this->campHalfHeight);
    CV::color(0, 0, 0);
    CV::circleFill(x, y, radius, 50);
    this->move();
    CV::translate(0, 0);
  }
};
