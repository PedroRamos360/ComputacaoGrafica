#include "Block.h"

Block::Block(float x, float y, int lives)
{
  this->x = x;
  this->y = y;
  this->lives = lives;
}

void Block::render()
{
  CV::color(0, 0.7, 0);
  CV::rectFill(this->x, this->y, this->x + size, this->y - size);
  CV::color(0, 0, 0);
  CV::rect(this->x, this->y, this->x + size, this->y - size);
  Vector2 rectCenter = Vector2(this->x + this->size / 2 - to_string(this->lives).length() * 5, this->y - this->size / 2 - 4);
  CV::color(1, 1, 1);
  CV::text(rectCenter.x, rectCenter.y, to_string(this->lives).c_str());
}

void Block::decreaseLife()
{
  this->lives--;
}

int Block::getLives()
{
  return this->lives;
}