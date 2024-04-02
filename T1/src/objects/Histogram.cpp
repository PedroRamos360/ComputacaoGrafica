#include "Histogram.h"

Histogram::Histogram(int screenWidth, int screenHeight, Image *image)
{
  this->x = screenWidth / 2 - this->width / 2;
  this->y = screenHeight - 10;
  this->image = image;
  this->calculateHistogramValues();
}

void Histogram::initializeHistogramWithZeros()
{
  for (int i = 0; i < 256; i++)
  {
    this->histogram[i] = 0;
  }
}

void Histogram::calculateHistogramValues()
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
      switch (channel)
      {
      case H_GRAY:
        this->histogram[gray]++;
        break;
      case H_RED:
        this->histogram[static_cast<int>(r)]++;
        break;
      case H_GREEN:
        this->histogram[static_cast<int>(g)]++;
        break;
      case H_BLUE:
        this->histogram[static_cast<int>(b)]++;
        break;
      }
    }
  }
}

void Histogram::render()
{
  if (!this->shouldRender)
  {
    return;
  }
  switch (channel)
  {
  case H_GRAY:
    CV::color(0, 0, 0);
    break;
  case H_RED:
    CV::color(1, 0, 0);
    break;
  case H_GREEN:
    CV::color(0, 1, 0);
    break;
  case H_BLUE:
    CV::color(0, 0, 1);
    break;
  }
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

void Histogram::setShouldRender(bool shouldRender)
{
  this->shouldRender = shouldRender;
}

bool Histogram::getShouldRender()
{
  return this->shouldRender;
}

void Histogram::setChannel(HistogramChannel channel)
{
  this->channel = channel;
  calculateHistogramValues();
}