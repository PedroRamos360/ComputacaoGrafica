#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "./objects/Button.h"
#include <unistd.h>
#include "./objects/Bmp.h"
#include "./objects/Image.h"
#include <vector>
#include "./objects/ManipulatedImage.h"
#include "./objects/Histogram.h"

using namespace std;

int screenWidth = 800, screenHeight = 600;

vector<Button *> buttons;
vector<Image *> images;

ManipulatedImage *manipulatedImage = NULL;
Histogram *histogram = NULL;

int opcao = 50;
int mouseX, mouseY;

int xCircle = 250;
int yCircle = 250;
int circleRadius = 50;
int x = 0;
int y = 0;
int rotation = 0;
int mouseHold;

#define HISTOGRAM_SIZE 256

void DrawMouseScreenCoords()
{
  char str[100];
  sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
  CV::text(10, 300, str);
  sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
  CV::text(10, 320, str);
}

void setAllImagesAsNonPrimary()
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

void buttonCallback(Image *image)
{
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
}

void render()
{
  CV::translate(0, 0);
  if (manipulatedImage != NULL)
  {
    manipulatedImage->renderIsolatedChannel();
  }
  if (histogram != NULL)
  {
    histogram->renderGrayHistogram();
  }
  for (Image *image : images)
  {
    image->renderImage();
  }
  for (Button *bt : buttons)
  {
    bt->Render();
  }
}

void keyboard(int key)
{
}

void keyboardUp(int key)
{
  switch (key)
  {
  case 202: // right
    if (!images.back() == NULL)
      images.back()->rotateRight();
    break;
  case 200: // left
    if (!images.back() == NULL)
      images.back()->rotateLeft();
    break;
  case 114: // r
    if (!manipulatedImage == NULL)
      manipulatedImage->setChannel(RED);
    break;
  case 103: // g
    if (!manipulatedImage == NULL)
      manipulatedImage->setChannel(GREEN);
    break;
  case 98: // b
    if (!manipulatedImage == NULL)
      manipulatedImage->setChannel(BLUE);
    break;
  case 104: // h
    if (!histogram == NULL)
      histogram->setShouldRender(!histogram->getShouldRender());
    break;
  }
  printf("key: %d\n", key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  mouseX = x;
  mouseY = y;
  if (state == 1)
  {
    for (Button *button : buttons)
    {
      button->handleColision(x, y);
    }
    mouseHold = 0;
  }
  if (state == 0 || mouseHold)
  {
    mouseHold = 1;
    if (images.back() != NULL)
    {
      images.back()->handleColision(x, y);
    }
  }
}

int main(void)
{
  vector<string> images_address = {"T1/images/lena.bmp", "T1/images/tree.bmp", "T1/images/car.bmp"};
  int index = 0;
  for (string image : images_address)
  {
    Bmp *bmp = new Bmp(image.c_str());
    bmp->convertBGRtoRGB();
    Image *img = new Image(index * 100 + 10, index * 100 + 10, bmp);
    images.push_back(img);
    string label = "Carrega imagem " + to_string(index + 1);
    Button *bt = new Button(screenWidth - 200, 20 + 30 * index, 20, label, buttonCallback, img);
    buttons.push_back(bt);
    index++;
  }
  CV::init(screenWidth, screenHeight, "Leitor de imagens");
  CV::run();
}
