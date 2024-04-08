/*
Trabalho 1 - Computação Gráfica - Manipulação de Imagens
Autor: Pedro Henrique Warken Ramos

Recursos implementados:
- Rotação de imagens (FLIP)
- Renderização de imagens com larguras não divisíveis por 4
- Drag de imagens
- Renderização de histograma cinza (luminância) e RGB
- Renderização de imagens com canal isolado R, G e B
- Quadro ao redor da imagem para indicar qual é a imagem principal

Funcionalidades bônus implementadas:
- Aumento e diminuição do brilho da imagem
- Aumento e diminuição do contraste da imagem

Informações importantes:
- A rotação das imagens é feita com as setas para esquerda e direita do teclado
- Aumento de brilho na seta UP diminuição na seta DOWN
- Aumento de contraste na tecla V diminuição na tecla C
- Para arrastar a imagem é preciso clicar na imgem principal e segurar enquanto move o mouse
- Os botões de carregamento das imagens servem para mostrar elas e para deixar de mostrar,
se quiser selecionar uma nova imagem principal é só clicar para renderizar ela pelo menu de botões
- As demais funções são realizadas de forma auto explicativa no menu de botões
*/

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
#include "./objects/Histogram.h"
#include "./objects/ManipulatedImage.h"
#include "./objects/ButtonManager.h"

using namespace std;

int screenWidth = 800, screenHeight = 600;

vector<Image *> images;

ManipulatedImage *manipulatedImage = NULL;
Histogram *histogram = NULL;
ButtonManager *buttonManager = NULL;

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

void render()
{
  CV::translate(0, 0);
  if (manipulatedImage != NULL)
  {
    manipulatedImage->renderIsolatedChannel();
  }
  if (histogram != NULL)
  {
    histogram->render();
  }
  for (Image *image : images)
  {
    image->renderImage();
  }
  buttonManager->render();
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
  case 201:
    if (!images.back() == NULL)
      images.back()->increaseBrightness();
    break;
  case 203:
    if (!images.back() == NULL)
      images.back()->decreaseBrightness();
    break;
  case 'c':
    if (!images.back() == NULL)
      images.back()->decreaseContrast();
    break;
  case 'v':
    if (!images.back() == NULL)
      images.back()->increaseContrast();
    break;
  }
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  mouseX = x;
  mouseY = y;
  if (state == 1)
  {
    buttonManager->handleColisions(x, y);
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
  vector<string> images_address = {"T1_PedroRamos/images/lenabugada.bmp", "T1_PedroRamos/images/treebugada.bmp", "T1_PedroRamos/images/carbugado.bmp"};
  int index = 0;
  for (string image : images_address)
  {
    Bmp *bmp = new Bmp(image.c_str());
    bmp->convertBGRtoRGB();
    Image *img = new Image(index * 100 + 10, index * 100 + 10, bmp);
    images.push_back(img);
    index++;
  }
  buttonManager = new ButtonManager(images, screenWidth, screenHeight, histogram, manipulatedImage);
  CV::init(screenWidth, screenHeight, "Leitor de imagens (Use as setas do teclado para rotacionar)");
  CV::run();
}
