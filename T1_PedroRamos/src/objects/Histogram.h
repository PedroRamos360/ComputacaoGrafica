/*
Classe para renderizar o histograma, realiza o cálculo dos valores do histograma conforme a imagem principal
é alterada e faz a renderização do histograma, a função setChannel é usada para escolher o histograma de qual
canal será renderizado.
*/

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Image.h"
#include <map>
#include <random>

using namespace std;

enum HistogramChannel
{
  H_GRAY = 0,
  H_RED = 1,
  H_GREEN = 2,
  H_BLUE = 3,
};

class Histogram
{
private:
  int x, y, width = 256, height = 256;
  int histogram[256];
  bool shouldRender = false;
  HistogramChannel channel = H_GRAY;
  Image *image;

  void initializeHistogramWithZeros();
  void calculateHistogramValues();

public:
  Histogram(int screenWidth, int screenHeight, Image *image);
  void render();
  void setShouldRender(bool shouldRender);
  bool getShouldRender();
  void setChannel(HistogramChannel channel);
};

#endif // HISTOGRAM_H
