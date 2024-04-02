#include "Image.h"
#include <vector>
#include "Histogram.h"
#include "ManipulatedImage.h"
#include "Button.h"
#include <string.h>
#include <map>

using namespace std;

#define BUTTON_HEIGHT 20

class ButtonManager
{
private:
  vector<Image *> &images;
  ManipulatedImage *&manipulatedImage;
  Histogram *&histogram;
  vector<Button *> buttons;
  int screenWidth, screenHeight;

  void
  setAllImagesAsNonPrimary()
  {
    for (Image *img : images)
    {
      img->setPrimaryImage(false);
    }
  }

  void orderImagesByPrimary(Image *image)
  {
    for (int i = 0; i < images.size(); i++)
    {
      if (images[i] == image)
      {
        Image *primaryImage = images[i];
        images.erase(images.begin() + i);
        images.push_back(primaryImage);
        break;
      }
    }
  }

  Image *getLastVisibleImage()
  {
    for (int i = images.size() - 1; i >= 0; i--)
    {
      Image *image = images[i];
      if (image->getShouldRender())
      {
        return image;
      }
    }
    return NULL;
  }

  void createImageAssociatedButton(int index, Image *image)
  {
    string label = "Carrega imagem " + to_string(index + 1);
    float x = this->screenWidth - 200;
    float y = 20 + 30 * index;
    auto buttonCallback = [image, this]()
    {
      if (image == NULL)
      {
        return;
      }
      image->setShouldRender(!image->getShouldRender());
      setAllImagesAsNonPrimary();
      if (image->getShouldRender())
      {
        orderImagesByPrimary(image);
        image->setPrimaryImage(true);
        manipulatedImage = new ManipulatedImage(image, screenWidth, screenHeight);
        histogram = new Histogram(screenWidth, screenHeight, image);
      }
      else
      {
        Image *primaryImage = getLastVisibleImage();
        if (!primaryImage == NULL)
        {
          orderImagesByPrimary(primaryImage);
          primaryImage->setPrimaryImage(true);
          manipulatedImage = new ManipulatedImage(primaryImage, screenWidth, screenHeight);
          histogram = new Histogram(screenWidth, screenHeight, primaryImage);
        }
      }
    };

    Button *bt = new Button(x, y, BUTTON_HEIGHT, label, buttonCallback);
    buttons.push_back(bt);
  }

  void createButtonsForColorChannels(int *lastY)
  {
    int buttonX = screenWidth - 200;
    vector<string> channelButtons = {"Imagem Vermelha", "Imagem Verde", "Imagem Azul"};
    for (string channelButton : channelButtons)
    {
      auto channelButtonCallback = [this, channelButton]()
      {
        if (manipulatedImage == NULL)
          return;
        Channel channel;
        if (channelButton == "Imagem Vermelha")
          channel = RED;
        else if (channelButton == "Imagem Verde")
          channel = GREEN;
        else
          channel = BLUE;

        manipulatedImage->setChannel(channel);
      };
      *lastY += 30;
      Button *button = new Button(buttonX, *lastY, BUTTON_HEIGHT, channelButton, channelButtonCallback);
      buttons.push_back(button);
    }
  }

  void createHistogramButton(int *lastY)
  {
    map<string, HistogramChannel> channelMap;
    channelMap["0Histograma cinza"] = H_GRAY;
    channelMap["1Histograma vermelho"] = H_RED;
    channelMap["2Histograma verde"] = H_GREEN;
    channelMap["3Histograma azul"] = H_BLUE;

    for (auto const &[label, channel] : channelMap)
    {
      auto histButtonCallback = [this, channel]()
      {
        if (histogram == NULL)
          return;
        histogram->setShouldRender(true);
        histogram->setChannel(channel);
      };
      float histButtonX = screenWidth - 200;
      float histButtonY = *lastY;
      string labelCopy = label;
      labelCopy.erase(labelCopy.begin());
      Button *histogramButton = new Button(histButtonX, histButtonY, BUTTON_HEIGHT, labelCopy, histButtonCallback);
      buttons.push_back(histogramButton);
      *lastY += 30;
    }
  }

  void init()
  {
    int index = 0;
    for (Image *image : this->images)
    {
      createImageAssociatedButton(index, image);
      index++;
    }
    int lastY = 20 + 30 * index;
    createHistogramButton(&lastY);
    createButtonsForColorChannels(&lastY);
  }

public:
  ButtonManager(vector<Image *> &images, int screenWidth, int screenHeight, Histogram *&histogram, ManipulatedImage *&manipulatedImage)
      : images(images), screenWidth(screenWidth), screenHeight(screenHeight), histogram(histogram), manipulatedImage(manipulatedImage)
  {
    init();
  }

  void handleColisions(int mouseX, int mouseY)
  {
    for (Button *button : buttons)
    {
      button->handleColision(mouseX, mouseY);
    }
  }

  void render()
  {
    for (Button *button : buttons)
    {
      button->Render();
    }
  }
};