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
