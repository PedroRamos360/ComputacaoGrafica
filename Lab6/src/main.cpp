#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vector3.h"

#include "gl_canvas2d.h"
int screenWidth = 500, screenHeight = 500;

float angInit = 0;

Vector3 rotacionaY(Vector3 p, float ang);
Vector3 transladaZ(Vector3 p, float d);
Vector2 project(Vector3 p, float d);
void desenha(Vector2 *p);

Vector3 entrada[8] = {
    Vector3(-1, -1, -1),
    Vector3(1, -1, -1),
    Vector3(1, 1, -1),
    Vector3(-1, 1, -1),
    Vector3(-1, -1, 1),
    Vector3(1, -1, 1),
    Vector3(1, 1, 1),
    Vector3(-1, 1, 1)};
void render()
{
  CV::translate(250, 250);
  Vector3 p;
  Vector2 saida[8];
  for (int i = 0; i < 8; i++)
  {
    p = entrada[i];
    p = rotacionaY(p, angInit);
    p = transladaZ(p, 3);
    saida[i] = project(p, 100);
  }
  desenha(saida);
  angInit += 0.01;
  Sleep(10);
}

Vector3 rotacionaY(Vector3 p, float ang)
{
  Vector3 r;
  r.x = p.x * cos(ang) - p.z * sin(ang);
  r.y = p.y;
  r.z = p.x * sin(ang) + p.z * cos(ang);
  return r;
}

Vector3 transladaZ(Vector3 p, float d)
{
  Vector3 r;
  r.x = p.x;
  r.y = p.y;
  r.z = p.z + d;
  return r;
}

Vector2 project(Vector3 p, float d)
{
  Vector2 r;
  r.x = p.x * d / p.z;
  r.y = p.y * d / p.z;
  return r;
}

void desenha(Vector2 p[8])
{
  CV::color(1, 0, 0);
  CV::line(p[0].x, p[0].y, p[1].x, p[1].y);
  CV::line(p[1].x, p[1].y, p[2].x, p[2].y);
  CV::line(p[2].x, p[2].y, p[3].x, p[3].y);
  CV::line(p[3].x, p[3].y, p[0].x, p[0].y);

  CV::line(p[4].x, p[4].y, p[5].x, p[5].y);
  CV::line(p[5].x, p[5].y, p[6].x, p[6].y);
  CV::line(p[6].x, p[6].y, p[7].x, p[7].y);
  CV::line(p[7].x, p[7].y, p[4].x, p[4].y);

  CV::line(p[0].x, p[0].y, p[4].x, p[4].y);
  CV::line(p[1].x, p[1].y, p[5].x, p[5].y);
  CV::line(p[2].x, p[2].y, p[6].x, p[6].y);
  CV::line(p[3].x, p[3].y, p[7].x, p[7].y);
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
