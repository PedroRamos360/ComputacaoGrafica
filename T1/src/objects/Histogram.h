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

public:
  Histogram(int screenWidth, int screenHeight, Image *image)
  {
    this->x = screenWidth / 2 - this->width / 2;
    this->y = screenHeight - 10;
    this->image = image;
    this->calculateHistogramValues();
    printf("Histogram created\n");

    // Print histogram values
    for (int i = 0; i < 256; i++)
    {
      printf("Histogram[%d] = %d\n", i, this->histogram[i]);
    }
  }

  void initializeHistogramWithZeros()
  {
    for (int i = 0; i < 256; i++)
    {
      this->histogram[i] = 0;
    }
  }

  void calculateHistogramValues()
  {
    this->initializeHistogramWithZeros();
    Bmp *bmp = this->image->getBmp();
    for (int h = 0; h < bmp->getHeight(); h++)
    {
      for (int w = 0; w < bmp->getWidth(); w++)
      {
        int pos = (h * bmp->getWidth() + w) * RGB_SIZE;
        float r = bmp->getImage()[pos];
        float g = bmp->getImage()[pos + 1];
        float b = bmp->getImage()[pos + 2];
        int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
        this->histogram[gray]++;
      }
    }
  }

  void renderGrayHistogram()
  {
    if (!this->shouldRender)
    {
      return;
    }
    CV::color(0, 0, 0);
    CV::rect(this->x, this->y, this->x + this->width, this->y - this->height);
    int partialWidth = this->width / 256;
    int maxCount = 0;
    for (int i = 0; i < 256; i++)
    {
      if (this->histogram[i] > maxCount)
      {
        maxCount = this->histogram[i];
      }
    }
    for (int i = 0; i < 256; i++)
    {
      int barHeight = static_cast<int>(static_cast<double>(this->histogram[i]) / maxCount * this->height);
      Point start = {this->x + i * partialWidth, this->y};
      Point end = {this->x + (i + 1) * partialWidth, this->y - barHeight};
      CV::rectFill(start.x, start.y, end.x, end.y);
    }
  }

  void setShouldRender(bool shouldRender)
  {
    this->shouldRender = shouldRender;
  }

  bool getShouldRender()
  {
    return this->shouldRender;
  }
};