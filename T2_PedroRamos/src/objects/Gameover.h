#include "../gl_canvas2d.h"
#include <string>
#include <iostream>

using namespace std;

#define PIXELS_BY_CHAR 10

class Gameover
{
private:
  float x, y;
  int *screenHeight, *screenWidth, finalScore;

public:
  Gameover(int *screenHeight, int *screenWidth, int finalScore)
  {
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->finalScore = finalScore;
  }

  void render()
  {
    CV::translate(*this->screenWidth / 2, *this->screenHeight / 2);
    CV::color(1, 0, 0);
    string gameOver = "Game Over";
    int xGameOver = gameOver.length() / 2 * PIXELS_BY_CHAR;
    CV::text(-xGameOver, 40, gameOver.c_str());
    CV::color(0, 0, 0);
    string score = "Score: " + to_string(this->finalScore);
    int xScore = score.length() / 2 * PIXELS_BY_CHAR;
    CV::text(-xScore, 20, score.c_str());
    CV::translate(0, 0);
  }
};