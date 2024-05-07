#include "../gl_canvas2d.h"
#include <string>
#include <iostream>

#define SCORE_BOARD_PADDING 20

using namespace std;

class ScoreBoard
{
private:
  int ballsCount = 1;
  int *screenWidth, *screenHeight;
  int campHalfWidth, campHalfHeight;

public:
  ScoreBoard(int *screenWidth, int *screenHeight, int campHalfWidth, int campHalfHeight)
  {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->campHalfWidth = campHalfWidth;
    this->campHalfHeight = campHalfHeight;
  }

  void render()
  {
    CV::translate(*this->screenWidth / 2 + this->campHalfWidth + SCORE_BOARD_PADDING, *this->screenHeight / 2 + this->campHalfHeight);
    CV::color(0, 0, 0);
    string ballsCountText = "Balls: " + to_string(this->ballsCount);
    CV::text(0, 0, ballsCountText.c_str());
    CV::translate(0, 0);
  }

  int getBallsCount()
  {
    return this->ballsCount;
  }

  void increaseScore()
  {
    this->ballsCount++;
  }

  void reset()
  {
    this->ballsCount = 1;
  }
};