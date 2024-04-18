#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "objects/Camp.h"

#include "gl_canvas2d.h"

int screenWidth = 1280, screenHeight = 720;

void render()
{
  Camp *camp = new Camp(screenWidth, screenHeight);
  camp->render();
  free(camp);
}

void keyboard(int key)
{
}

void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
}

int main(void)
{
  CV::init(screenWidth, screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
  CV::run();
}
