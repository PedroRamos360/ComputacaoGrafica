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

vector<Button> buttons;
vector<Image> images;

Image *mainImage = NULL;

int opcao = 50;
int mouseX, mouseY;

int xCircle = 250;
int yCircle = 250;
int circleRadius = 50;
int x = 0;
int y = 0;
int rotation = 0;

void DrawMouseScreenCoords()
{
  char str[100];
  sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
  CV::text(10, 300, str);
  sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
  CV::text(10, 320, str);
}

void buttonCallback(Image *image)
{
  image->setShouldRender(true);
}

void render()
{
  CV::translate(x, y);
  CV::color(1, 1, 1);
  CV::rectFill(0, 0, screenWidth, screenHeight);
  for (int i = 0; i < 3; i++)
  {
    string label = "Carrega imagem " + to_string(i + 1);
    Button *bt = new Button(screenWidth - 200, 20 + 30 * i, 20, label, buttonCallback, &images[i]);
    buttons.push_back(*bt);
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
    printf("\nRight");
    mainImage->rotateRight();
    break;
  case 200: // left
    printf("\nLeft");
    mainImage->rotateLeft();
    break;
  }
  printf("\nLiberou: %d", key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  if (state == 1)
  {
    for (Button button : buttons)
    {
      button.handleColision(x, y);
    }
  }
}

int main(void)
{
  vector<string> images = {"T1/images/lena.bmp", "T1/images/lena.bmp", "T1/images/lena.bmp"};
  int index = 0;
  for (string image : images)
  {
    Bmp *bmp = new Bmp(image.c_str());
    bmp->convertBGRtoRGB();
    Image *img = new Image(0, index * 50, bmp);
    index++;
  }
  CV::init(screenWidth, screenHeight, "Leitor de imagens");
  CV::run();
}
