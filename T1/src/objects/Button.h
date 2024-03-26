#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "../gl_canvas2d.h"
#include <iostream>
#include <string.h>
#include "Image.h"
using namespace std;

class Button
{
  float height, width, x, y;
  void (*onClick)(Image *);
  Image *image;
  string label;

public:
  Button(float _x, float _y, float _alt, string _label, void (*_onClick)(Image *), Image *_image)
  {
    height = _alt;
    width = _label.size() * 11;
    x = _x;
    y = _y;
    label = _label;
    onClick = _onClick;
    image = _image;
  }

  void Render()
  {
    CV::color(0, 1, 0);
    CV::rectFill(x, y, x + width, y + height);
    CV::color(0, 0, 0);
    CV::text(x + label.size() / 1.5, y + height / 2, label.c_str());
  }

  void handleColision(int mouseX, int mouseY)
  {
    if (mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
    {
      printf("=================== CLICOU +=================== \n");
      if (image == NULL)
      {
        printf("image não é null\n");
        onClick(image);
      }
    }
  }
};

#endif
