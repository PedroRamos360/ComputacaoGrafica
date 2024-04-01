#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Image.h"
#include <map>
#include <random>

using namespace std;

class Histogram
{
private:
  int x, y, width = 256, height = 256;
  int histogram[256];
  bool shouldRender = false;
  Image *image;

  void initializeHistogramWithZeros();
  void calculateHistogramValues();

public:
  Histogram(int screenWidth, int screenHeight, Image *image);
  void renderGrayHistogram();
  void setShouldRender(bool shouldRender);
  bool getShouldRender();
};

#endif // HISTOGRAM_H
