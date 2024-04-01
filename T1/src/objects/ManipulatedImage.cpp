#include "ManipulatedImage.h"

ManipulatedImage::ManipulatedImage(Image *image, int screenWidth, int screenHeight)
{
  this->img = image->getBmp();
  this->x = screenWidth - img->getWidth();
  this->y = screenHeight - img->getHeight();
}

int ManipulatedImage::invertY(int y)
{
  return img->getHeight() - y;
}

void ManipulatedImage::renderIsolatedChannel()
{
  if (this->channel == NONE)
    return;
  for (int h = 0; h < img->getHeight(); h++)
  {
    for (int w = 0; w < img->getWidth(); w++)
    {
      int pos = (h * img->getWidth() + w) * RGB_SIZE;
      float r = img->getImage()[pos] / 255.0f;
      float g = img->getImage()[pos + 1] / 255.0f;
      float b = img->getImage()[pos + 2] / 255.0f;
      if (this->channel == RED)
        CV::color(r, 0, 0);
      else if (this->channel == GREEN)
        CV::color(0, g, 0);
      else if (this->channel == BLUE)
        CV::color(0, 0, b);
      CV::point(w + this->x, invertY(h) + this->y);
    }
  }
}

void ManipulatedImage::setChannel(Channel channel)
{
  this->channel = channel;
}