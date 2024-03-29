#ifndef IMAGE_H
#define IMAGE_H

#include "Bmp.h"
#include "../gl_canvas2d.h"

#define UP 3
#define LEFT 4
#define DOWN 1
#define RIGHT 2

#define RGB_SIZE 3

struct ColisionCoords
{
  int xStart;
  int xEnd;
  int yStart;
  int yEnd;
};

struct Point
{
  int x;
  int y;
};

class Image
{
private:
  int x, y, rotation = 3;
  Bmp *img;
  bool shouldRender;
  bool primaryImage = true;

  int invertX(int x)
  {
    return img->getWidth() - x;
  }

  int invertY(int y)
  {
    return img->getHeight() - y;
  }

  Point rotatePoint(Point point)
  {
    int centerX = this->x + img->getWidth() / 2;
    int centerY = this->y + img->getHeight() / 2;
    int translatedX = x - centerX;
    int translatedY = y - centerY;
    int rotatedX, rotatedY;
    switch (this->rotation)
    {
    case UP:
      rotatedX = translatedX;
      rotatedY = -translatedY;
      break;
    case DOWN:
      rotatedX = -translatedX;
      rotatedY = translatedY;
      break;
    case LEFT:
      rotatedX = -translatedY;
      rotatedY = -translatedX;
      break;
    case RIGHT:
      rotatedX = translatedY;
      rotatedY = translatedX;
      break;
    default:
      rotatedX = translatedX;
      rotatedY = translatedY;
      break;
    }
    Point output;
    output.x = rotatedX + centerX;
    output.y = rotatedY + centerY;
    return output;
  }

  void renderPoint(int x, int y)
  {
    int centerX = this->x + img->getWidth() / 2;
    int centerY = this->y + img->getHeight() / 2;

    int translatedX = x - centerX;
    int translatedY = y - centerY;

    int rotatedX, rotatedY;

    switch (this->rotation)
    {
    case UP:
      rotatedX = translatedX;
      rotatedY = -translatedY;
      break;
    case DOWN:
      rotatedX = -translatedX;
      rotatedY = translatedY;
      break;
    case LEFT:
      rotatedX = -translatedY;
      rotatedY = -translatedX;
      break;
    case RIGHT:
      rotatedX = translatedY;
      rotatedY = translatedX;
      break;
    default:
      rotatedX = translatedX;
      rotatedY = translatedY;
      break;
    }

    int manipulatedX = rotatedX + centerX;
    int manipulatedY = rotatedY + centerY;

    CV::point(manipulatedX, manipulatedY);
  }

  void drawImage()
  {
    for (int h = 0; h < img->getHeight(); h++)
    {
      for (int w = 0; w < img->getWidth(); w++)
      {
        int pos = (h * img->getWidth() + w) * RGB_SIZE;
        float r = img->getImage()[pos] / 255.0f;
        float g = img->getImage()[pos + 1] / 255.0f;
        float b = img->getImage()[pos + 2] / 255.0f;
        CV::color(r, g, b);
        this->renderPoint(w + this->x, h + this->y);
        this->drawImageCanvas(h, w);
      }
    }
  }

  void drawImageCanvas(int h, int w)
  {
    if (!this->primaryImage)
    {
      return;
    }
    if (h == 0)
    {
      CV::color(0.5, 0.5, 0.5);
      for (int i = 0; i < 5; i++)
      {
        this->renderPoint(w + this->x, this->y - i);
        this->renderPoint(w + this->x, this->y + i + img->getHeight());
      }
    }
    if (w == 0)
    {
      CV::color(0.5, 0.5, 0.5);
      for (int i = 0; i < 5; i++)
      {
        this->renderPoint(this->x - i, h + this->y);
        this->renderPoint(this->x + i + img->getWidth(), h + this->y);
      }
    }
  }

  ColisionCoords getColisionCoords()
  {
    int manipulatedX = this->x;
    int manipulatedY = this->y;
    switch (rotation)
    {
    case UP:
      manipulatedY *= -1;
      break;
    case DOWN:
      manipulatedX *= -1;
      break;
    case RIGHT:
      manipulatedX = this->y;
      manipulatedY = this->x;
      break;
    case LEFT:
      manipulatedX = this->y * -1;
      manipulatedY = this->x * -1;
      break;
    }

    ColisionCoords output;

    output.xStart = manipulatedX;
    output.xEnd = manipulatedX + img->getWidth();
    output.yStart = manipulatedY;
    output.yEnd = manipulatedY + img->getHeight();

    return output;
  }

  void drawImageBorder()
  {
    CV::color(0, 0, 0);
    ColisionCoords coords = getColisionCoords();
    CV::rect(coords.xStart, coords.yStart, coords.xEnd, coords.yEnd);
  }

public:
  Image(int x, int y, Bmp *img)
  {
    this->x = x;
    this->y = y;
    this->img = img;
    this->shouldRender = false;
  }

  void renderImage()
  {
    if (img != NULL && this->shouldRender)
    {
      this->drawImage();
      this->drawImageBorder();
    }
  }

  void handleColision(int x, int y)
  {
    ColisionCoords coords = getColisionCoords();
    bool colision = x >= coords.xStart && x <= coords.xEnd && y >= coords.yStart && y <= coords.yEnd;
    if (colision)
    {
      int manipulatedX = x;
      int manipulatedY = y;
      switch (rotation)
      {
      case UP:
        manipulatedY = invertY(y);
        break;
      case DOWN:
        manipulatedX = invertX(x);
        break;
      case LEFT:
        manipulatedX = invertX(y);
        manipulatedY = invertY(x);
        break;
      case RIGHT:
        manipulatedX = y;
        manipulatedY = x;
        break;
      }
      this->x = manipulatedX - img->getWidth() / 2;
      this->y = manipulatedY - img->getHeight() / 2;
    }
  }

  void rotateLeft()
  {
    if (this->rotation > 1)
      this->rotation -= 1;
    else
      this->rotation = 4;
  }

  void rotateRight()
  {
    if (this->rotation < 4)
      this->rotation += 1;
    else
      this->rotation = 1;
  }

  bool getShouldRender()
  {
    return shouldRender;
  }

  void setShouldRender(bool value)
  {
    shouldRender = value;
  }

  void setPrimaryImage(bool value)
  {
    primaryImage = value;
  }
};

#endif
