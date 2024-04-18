#include "../gl_canvas2d.h"
#include "Ball.h"
#include <vector>

struct Point
{
  int x, y;
};

using namespace std;

class Player
{
private:
  int x, y;
  int lineSize = 100;
  int *mouseX, *mouseY;
  int *screenWidth, *screenHeight;
  int campHalfWidth;
  int campHalfHeight;
  Point origin;
  vector<Ball *> &balls;

  Vector2 getDirection()
  {
    Vector2 direction = Vector2(*mouseX - this->origin.x, *mouseY - this->origin.y);
    direction.normalize();
    return direction;
  }

  void drawAim()
  {
    CV::color(0, 0, 0);
    Vector2 direction = getDirection();
    direction.normalize();
    float angle = atan2(direction.y, direction.x);
    if (angle < 0)
      angle += 2 * PI;
    direction = direction * lineSize;
    if (angle >= 0 && angle <= PI)
      CV::line(0, 0, direction.x, direction.y);
  }

public:
  Player(int *mouseX, int *mouseY, int *screenWidth, int *screenHeight, int campHalfWidth, int campHalfHeight, vector<Ball *> &balls)
      : mouseX(mouseX), mouseY(mouseY), screenWidth(screenWidth), screenHeight(screenHeight), campHalfWidth(campHalfWidth),
        campHalfHeight(campHalfHeight), balls(balls)
  {
    origin = {*screenWidth / 2, *screenHeight / 2 - this->campHalfHeight};
  }

  void shoot()
  {
    Vector2 direction = getDirection();
    Ball *ball = new Ball(direction, screenWidth, screenHeight, campHalfWidth, campHalfHeight);
    balls.push_back(ball);
  }

  void render()
  {
    CV::translate(origin.x, origin.y);
    drawAim();
    CV::translate(0, 0);
  }
};