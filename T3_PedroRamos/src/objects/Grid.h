/* Classe que Lida com toda lógica de renderizar os blocos em conjunto em um sistema de grid
e geração aleatória de blocos, define quantas vidas cada bloco tem a progressão de dificuldade
e a redução da altura dos blocos quando passa de nível e também tem uma função de reset para
quando o jogador reinicia o jogo*/

#include <vector>
#include "Block.h"
#include "../Vector2.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>

using namespace std;

class Grid
{
private:
  int campHalfWidth, campHalfHeight, *screenWidth, *screenHeight;
  vector<Block *> blocks;

  void allocateBlocks(int lifes)
  {
    Vector2 campStart = Vector2(-this->campHalfWidth, this->campHalfHeight * 2);
    random_device rd;
    unsigned seed = getEpochTime();
    string chars = "1";
    for (int i = 0; i < 6; i++)
    {
      int randomBit = rand() % 2;
      chars += to_string(randomBit);
    }
    shuffle(chars.begin(), chars.end(), default_random_engine(seed));
    for (int i = 0; i < 8; i++)
    {
      if (chars[i] == '1')
      {
        Block *block = new Block(campStart.x, campStart.y, lifes);
        blocks.push_back(block);
      }
      campStart.x += BLOCK_SIZE;
    }
  }

public:
  Grid(int campHalfWidth, int campHalfHeight, int *screenWidth, int *screenHeight)
  {
    this->campHalfHeight = campHalfHeight;
    this->campHalfWidth = campHalfWidth;
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    allocateBlocks(1);
  }

  void render()
  {
    CV::translate(*screenWidth / 2, *screenHeight / 2 - this->campHalfHeight);
    for (int i = 0; i < blocks.size(); i++)
    {
      if (blocks[i]->getLives() > 0)
      {
        blocks[i]->render();
      }
      else
      {
        delete blocks[i];
        blocks.erase(blocks.begin() + i);
      }
    }
    CV::translate(0, 0);
  }

  vector<Block *> getBlocks()
  {
    return this->blocks;
  }

  void reduceBlocksHeight(int score)
  {
    for (int i = 0; i < blocks.size(); i++)
    {
      blocks[i]->y -= blocks[i]->size;
    }
    int difficulty = (score / 10) * 10;
    this->allocateBlocks(score + difficulty);
  }

  bool checkGameOver()
  {
    for (int i = 0; i < blocks.size(); i++)
    {
      if (blocks[i]->y <= blocks[i]->size)
      {
        return true;
      }
    }
    return false;
  }

  void reset()
  {
    for (int i = 0; i < blocks.size(); i++)
    {
      delete blocks[i];
    }
    blocks.clear();
    allocateBlocks(1);
  }
};
