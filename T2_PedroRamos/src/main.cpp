#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "objects/Camp.h"

#include "gl_canvas2d.h"

int screenWidth = 1280, screenHeight = 720;
int mouseX = 0, mouseY = 0;

Camp *camp = NULL;

void render()
{
  camp->render();
}

void keyboard(int key)
{
}

void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  mouseX = x;
  mouseY = y;
  if (state == 1)
  {
    camp->handleMouseClick();
  }
}

int main(void)
{
  camp = new Camp(&screenWidth, &screenHeight, &mouseX, &mouseY);
  CV::init(screenWidth, screenHeight, "Balance as bolas!");
  CV::run();
}
