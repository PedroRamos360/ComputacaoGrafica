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
  ManipulatedImage(Image *image, int screenWidth, int screenHeight)
  {
    this->img = image->getBmp();
    this->x = screenWidth - img->getWidth();
    this->y = screenHeight - img->getHeight();
  }

  int invertY(int y)
  {
    return img->getHeight() - y;
  }

  void renderIsolatedChannel()
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

  void setChannel(Channel channel)
  {
    this->channel = channel;
  }
};