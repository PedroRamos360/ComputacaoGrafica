#ifndef IMAGE_H
#define IMAGE_H

#include "Bmp.h"
#include "../gl_canvas2d.h"

#define UP 3
#define LEFT 4
#define DOWN 1
#define RIGHT 2

#define RGB_SIZE 3

class Image
{
private:
  int x, y, rotation = 3;
  Bmp *img;
  bool shouldRender;
  bool primaryImage = true;
  int lastColisionX = NULL;
  int lastColisionY = NULL;
  void renderPoint(int x, int y)
  {
    int manipulatedX = x;
    int manipulatedY = y;
    if (this->rotation == UP || this->rotation == LEFT)
    {
      manipulatedY = img->getHeight() - y;
    }
    if (this->rotation == DOWN || this->rotation == LEFT)
    {
      manipulatedX = img->getWidth() - x;
    }
    if (this->rotation == RIGHT || this->rotation == LEFT)
    {
      CV::point(manipulatedY, manipulatedX);
      return;
    }
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

  void drawImageBorder()
  {
    CV::color(0, 0, 0);
    CV::rect(this->x, this->y, this->x + img->getWidth(), this->y + img->getHeight());
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
      // this->drawImageBorder();
    }
  }

  void handleColision(int x, int y)
  {
    bool colision;
    int yMultiplier = 1;
    int xMultiplier = 1;
    switch (rotation)
    {
    case UP:
      yMultiplier = -1;
      break;
    case LEFT:
      xMultiplier = -1;
      break;
    case DOWN:
      yMultiplier = 1;
      break;
    case RIGHT:
      xMultiplier = 1;
      break;
    }
    int multipliedX = this->x * xMultiplier;
    int multipliedY = this->y * yMultiplier;
    colision = x >= multipliedX && x <= multipliedX + img->getWidth() && y >= multipliedY && y <= multipliedY + img->getHeight();

    if (colision)
    {
      this->x = x - img->getWidth() / 2;
      this->y = y - img->getHeight() / 2;
      // if (this->lastColisionX && this->lastColisionY)
      // {
      //   if (rotation == UP || rotation == DOWN)
      //   {
      //     this->x += (x - this->lastColisionX) * xMultiplier;
      //     this->y += (y - this->lastColisionY) * yMultiplier;
      //   }
      //   if (rotation == LEFT || rotation == RIGHT)
      //   {
      //     this->x += (y - this->lastColisionY) * yMultiplier;
      //     this->y += (x - this->lastColisionX) * xMultiplier;
      //   }
      // }
      // this->lastColisionX = x;
      // this->lastColisionY = y;
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
