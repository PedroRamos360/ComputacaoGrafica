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
  void renderPoint(int x, int y, bool flip)
  {
    if (flip)
    {
      CV::point(y, x);
    }
    else
    {
      CV::point(x, y);
    }
  }

public:
  int x, y, rotation = 3;
  Bmp *img;
  Image(int x, int y, Bmp *img)
  {
    this->x = x;
    this->y = y;
    this->img = img;
  }

  void renderImage()
  {
    printf("\nRotation: %d", this->rotation);
    if (img != NULL)
    {
      for (int h = 0; h < img->getHeight(); h++)
      {
        for (int w = 0; w < img->getWidth(); w++)
        {
          int yinv;
          int xinv;
          if (this->rotation == DOWN || this->rotation == LEFT)
          {
            yinv = h;
          }
          else
          {
            yinv = img->getHeight() - h;
          }
          if (this->rotation == DOWN || this->rotation == RIGHT)
          {
            xinv = img->getWidth() - w;
          }
          else
          {
            xinv = w;
          }
          int pos = (yinv * img->getWidth() + xinv) * RGB_SIZE;
          float r = img->getImage()[pos] / 255.0f;
          float g = img->getImage()[pos + 1] / 255.0f;
          float b = img->getImage()[pos + 2] / 255.0f;
          CV::color(r, g, b);
          this->renderPoint(w, h, this->rotation == LEFT || this->rotation == RIGHT);
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
};

#endif
