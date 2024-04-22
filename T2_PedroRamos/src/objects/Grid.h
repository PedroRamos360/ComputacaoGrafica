#include <vector>
#include "Block.h"
#include "../Vector2.h"

using namespace std;

class Grid
{
private:
  int campHalfWidth, campHalfHeight, *screenWidth, *screenHeight;
  vector<Block *> blocks;

  void allocateBlocks()
  {
    Vector2 campStart = Vector2(-this->campHalfWidth, this->campHalfHeight * 2);
    campStart.y -= 150;
    for (int i = 0; i < 8; i++)
    {
      Block *block = new Block(campStart.x, campStart.y, 10);
      campStart.x += block->size;
      blocks.push_back(block);
    }
  }

public:
  Grid(int campHalfWidth, int campHalfHeight, int *screenWidth, int *screenHeight)
  {
    this->campHalfHeight = campHalfHeight;
    this->campHalfWidth = campHalfWidth;
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    allocateBlocks();
  }

  void render()
  {
    CV::translate(*screenWidth / 2, *screenHeight / 2 - this->campHalfHeight);
    for (int i = 0; i < blocks.size(); i++)
    {
      blocks[i]->render();
    }
    CV::translate(0, 0);
  }

  vector<Block *> getBlocks()
  {
    return this->blocks;
  }
};
