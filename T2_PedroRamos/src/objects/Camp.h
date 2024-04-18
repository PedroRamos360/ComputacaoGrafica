#include <stdio.h>
#include <stdlib.h>
#include "../gl_canvas2d.h"

class Camp
{
private:
  int screenWidth, screenHeight;

public:
  Camp(int screenWidth, int screenHeight)
  {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
  }

  void render()
  {
    CV::translate(screenWidth / 2, screenHeight / 2);
    CV::color(0, 0, 0);
    CV::rect(-200, -300, 200, 300);
  }
};
