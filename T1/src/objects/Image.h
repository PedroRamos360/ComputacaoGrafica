#ifndef IMAGE_H
#define IMAGE_H

#include "Bmp.h"
#include "../gl_canvas2d.h"

#define UP 3
#define RIGHT 4
#define DOWN 1
#define LEFT 2

#define RGB_SIZE 3

class Image
{
private:
  int x, y, rotation = 3;
  Bmp *img;
  bool shouldRender;
  void renderPoint(int x, int y)
  {
    int manipulatedX = x;
    int manipulatedY = y;
    if (this->rotation == UP || this->rotation == RIGHT)
    {
      manipulatedY = img->getHeight() - y;
    }
    if (this->rotation == DOWN || this->rotation == RIGHT)
    {
      manipulatedX = img->getWidth() - x;
    }
    if (this->rotation == LEFT || this->rotation == RIGHT)
    {
      CV::point(manipulatedY, manipulatedX);
      return;
    }
    CV::point(manipulatedX, manipulatedY);
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
        }
      }
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
};

#endif
