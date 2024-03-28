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

using namespace std;

int screenWidth = 800, screenHeight = 600;

vector<Button *> buttons;
vector<Image *> images;

Image *mainImage = NULL;

int opcao = 50;
int mouseX, mouseY;

int xCircle = 250;
int yCircle = 250;
int circleRadius = 50;
int x = 0;
int y = 0;
int rotation = 0;
int mouseHold;

void DrawMouseScreenCoords()
{
  char str[100];
  sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
  CV::text(10, 300, str);
  sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
  CV::text(10, 320, str);
}

void setOtherImagesAsNonPrimary(Image *image)
{
  for (Image *img : images)
  {
    if (img != image)
    {
      img->setPrimaryImage(false);
    }
  }
}

void buttonCallback(Image *image)
{
  image->setShouldRender(!image->getShouldRender());
  image->setPrimaryImage(true);
  setOtherImagesAsNonPrimary(image);
  mainImage = image;
}

void render()
{
  CV::translate(0, 0);
  CV::color(1, 1, 1);
  CV::rectFill(0, 0, screenWidth, screenHeight);

  for (Image *image : images)
  {
    image->renderImage();
  }
  if (mainImage != NULL)
  {
    mainImage->renderImage();
  }
  for (Button *bt : buttons)
  {
    bt->Render();
  }
  DrawMouseScreenCoords();
}

void keyboard(int key)
{
}

void keyboardUp(int key)
{
  switch (key)
  {
  case 202: // right
    mainImage->rotateRight();
    break;
  case 200: // left
    mainImage->rotateLeft();
    break;
  }
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
    if (mainImage != NULL)
    {
      mainImage->handleColision(x, y);
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
    Image *img = new Image(index * 50 + 10, -index * 50 - 10, bmp);
    images.push_back(img);
    string label = "Carrega imagem " + to_string(index + 1);
    Button *bt = new Button(screenWidth - 200, 20 + 30 * index, 20, label, buttonCallback, img);
    buttons.push_back(bt);
    index++;
  }
  CV::init(screenWidth, screenHeight, "Leitor de imagens");
  CV::run();
}
