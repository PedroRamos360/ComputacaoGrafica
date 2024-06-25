#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
int screenWidth = 500, screenHeight = 500;
float angInit = 0;

void engrenage()
{
  CV::translate(250, 250);
  CV::color(1, 0, 0);
  float raio1 = 100, raio2 = 120, ang = 0;
  float raio = raio1;
  float lastX = raio1 * cos(ang + angInit);
  float lastY = raio1 * sin(ang + angInit);
  float passo = (2 * PI) / 80;
  for (ang; ang <= 2 * PI + passo; ang += passo)
  {
    float x1 = raio * cos(ang + angInit);
    float y1 = raio * sin(ang + angInit);
    ang += passo;
    float x2 = raio * cos(ang + angInit);
    float y2 = raio * sin(ang + angInit);
    CV::line(x1, y1, x2, y2);
    CV::line(lastX, lastY, x1, y1);
    lastX = x2;
    lastY = y2;
    if (raio == raio1)
      raio = raio2;
    else
      raio = raio1;
  }
  angInit -= 0.01;
}

void espiral()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  CV::color(0, 0, 0);
  float raio = 0;
  for (float a = 0; a <= 10 * PI; a += 0.01)
  {
    float x = raio * cos(a + angInit);
    float y = raio * sin(a + angInit);
    CV::point(x, y);
    raio += 0.01;
  }
  angInit -= 0.001;
}

void relogio(int h, int m)
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  CV::color(0, 0, 0);
  float passo = (2 * PI) / 12;
  float raio1 = 100;
  float raio2 = 120;
  CV::circle(0, 0, raio2, 100);
  for (float a = 0; a < 2 * PI; a += passo)
  {
    float x1 = raio1 * cos(a);
    float y1 = raio1 * sin(a);
    float x2 = raio2 * cos(a);
    float y2 = raio2 * sin(a);
    CV::line(x1, y1, x2, y2);
  }
  float x = 50 * cos(-passo * h + PI / 2);
  float y = 50 * sin(-passo * h + PI / 2);
  CV::line(0, 0, x, y);
  float min = (2 * PI) / 60;
  x = 80 * cos(-min * m + PI / 2);
  y = 80 * sin(-min * m + PI / 2);
  CV::line(0, 0, x, y);
}

int h, m = 0;
void render()
{
  relogio(h, m);
  h++;
  if (h > 12)
    h = 0;
  m++;
  if (m > 60)
    m = 0;
  Sleep(500);
}

void keyboard(int key)
{
  printf("\nTecla: %d", key);
}

void keyboardUp(int key)
{
  printf("\nLiberou: %d", key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
}

int main(void)
{
  CV::init(screenWidth, screenHeight, "Teste");
  CV::run();
}
