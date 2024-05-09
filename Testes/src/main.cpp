#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
int screenWidth = 500, screenHeight = 500;

float angInit = 0;

void render()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  float raio = 0;
  float ang = 0;
  CV::color(1, 0, 0);
  for (int i = 0; i < 2000; i++)
  {
    float x = raio * cos(angInit + ang);
    float y = raio * sin(angInit + ang);
    CV::point(x, y);
    raio += 0.1;
    ang -= 0.01;
  }
  angInit -= 0.001;
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
