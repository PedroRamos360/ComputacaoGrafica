#include "../gl_canvas2d.h"
#include "../Vector2.h"
#include <string>
#include <random>
#include <iostream>

using namespace std;

string generateUUID()
{
  static random_device rd;
  static mt19937 gen(rd());
  static uniform_int_distribution<> dis(0, 15);
  const char *hexChars = "0123456789abcdef";
  string uuid;
  uuid.reserve(36);
  for (int i = 0; i < 36; ++i)
  {
    if (i == 8 || i == 13 || i == 18 || i == 23)
    {
      uuid += '-';
    }
    else if (i == 14)
    {
      uuid += '4'; // Version 4 UUID
    }
    else if (i == 19)
    {
      uuid += hexChars[dis(gen) & 0x3 | 0x8]; // Variant 1 (RFC 4122)
    }
    else
    {
      uuid += hexChars[dis(gen)];
    }
  }

  return uuid;
}

class Block
{
private:
  int lives;
  string blockId;

public:
  float x, y;
  int size = 50;
  Block(float x, float y, int lives)
  {
    this->x = x;
    this->blockId = generateUUID();
    this->y = y;
    this->lives = lives;
  }

  void render()
  {
    CV::color(0, 0.7, 0);
    CV::rectFill(this->x, this->y, this->x + size, this->y - size);
    CV::color(0, 0, 0);
    CV::rect(this->x, this->y, this->x + size, this->y - size);
    Vector2 rectCenter = Vector2(this->x + this->size / 2 - to_string(this->lives).length() * 5, this->y - this->size / 2 - 4);
    CV::color(1, 1, 1);
    CV::text(rectCenter.x, rectCenter.y, to_string(this->lives).c_str());
  }

  void decreaseLife()
  {
    this->lives--;
  }

  int getLives()
  {
    return this->lives;
  }

  string getBlockId()
  {
    return this->blockId;
  }
};