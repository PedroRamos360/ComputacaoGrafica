#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <iostream>
#include "../gl_canvas2d.h"
#include "../Vector2.h"
#include <random>

using namespace std;

class Block
{
private:
  int lives;
  string blockId;

public:
  float x, y;
  int size = 50;
  Block(float x, float y, int lives);
  void render();
  void decreaseLife();
  int getLives();
  string getBlockId();
};

#endif // BLOCK_H