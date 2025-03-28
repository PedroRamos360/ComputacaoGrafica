/*
Classe para lidar com as imagens, cada uma das imagens geradas na tela é uma instância dessa classe,
através dela que é realizada a rotação, renderização, alterações em contraste e brilho, colisão da 
imagem com o mouse e o drag da imagem.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "Bmp.h"
#include "../gl_canvas2d.h"

#define UP 3
#define LEFT 4
#define DOWN 1
#define RIGHT 2

#define RGB_SIZE 3

struct ColisionCoords
{
  int xStart;
  int xEnd;
  int yStart;
  int yEnd;
};

struct Point
{
  int x;
  int y;
};

class Image
{
private:
  int x, y, rotation = 3;
  bool shouldRender;
  Bmp *img;
  bool primaryImage = true;
  int brightness = 0;
  float contrast = 1;

  int invertX(int x);
  int invertY(int y);
  Point rotatePoint(Point point);
  void renderPoint(int x, int y);
  void drawImage();
  void drawImageCanvas(int h, int w);
  ColisionCoords getColisionCoords();
  void drawImageBorder();

public:
  Image(int x, int y, Bmp *img);
  void renderImage();
  void handleColision(int x, int y);
  void rotateLeft();
  void rotateRight();
  bool getShouldRender();
  void setShouldRender(bool value);
  void setPrimaryImage(bool value);
  bool isPrimaryImage();
  Bmp *getBmp();
  int getWidth();
  int getHeight();
  void increaseBrightness();
  void decreaseBrightness();
  void increaseContrast();
  void decreaseContrast();
};

#endif // IMAGE_H