#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "./objects/Botao.h"
#include <unistd.h>
#include "./objects/Bmp.h"
#include "./objects/Image.h"

using namespace std;

int screenWidth = 500, screenHeight = 500;

Botao *bt = NULL;
int opcao = 50;
int mouseX, mouseY;

Bmp *img1 = NULL;
Image *mainImage = NULL;

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

void render()
{
  CV::translate(x, y);
  CV::color(1, 1, 1);
  CV::rectFill(0, 0, screenWidth, screenHeight);
  mainImage->renderImage();
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
}

int main(void)
{
  img1 = new Bmp("/home/pedro/Github/ComputacaoGrafica/T1/images/lena.bmp");
  mainImage = new Image(0, 0, img1);
  img1->convertBGRtoRGB();
  CV::init(screenWidth, screenHeight, "Leitor de imagens");
  CV::run();
}
