/*
Classe para gerar as imagens com canais separados RGB que é renderizada no canto da tela, poderia ter feito
junto na classe Image, mas como a implementação dessa é bem mais simples, sem rotações nem colisão, decidi
fazer em uma classe separada para isolar a lógica.
*/

#ifndef MANIPULATEDIMAGE_H
#define MANIPULATEDIMAGE_H

#include "Image.h"

enum Channel
{
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  NONE = 3
};

class ManipulatedImage
{
private:
  Bmp *img;
  int x;
  int y;
  Channel channel = NONE;

public:
  ManipulatedImage(Image *image, int screenWidth, int screenHeight);
  int invertY(int y);
  void renderIsolatedChannel();
  void setChannel(Channel channel);
};

#endif // MANIPULATEDIMAGE_H