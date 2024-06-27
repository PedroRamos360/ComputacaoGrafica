#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vector3.h"
#include "./Vector2.h"

#include "gl_canvas2d.h"
int screenWidth = 500, screenHeight = 500;

Vector3 rotateY(Vector3 p, float ang);
Vector3 translateZ(Vector3 p, float d);
Vector3 translateX(Vector3 p, float d);
Vector3 translateY(Vector3 p, float d);
Vector2 projeta(Vector3 p, float d);
void drawCilinder(Vector2 *p);
Vector3 *getCilinderPoints(float height, float raio);
Vector3 *getSidewaysCilinder(float height, float raio);
void renderPistonCapsule();
void renderPiston();
void renderCrank();

int totalPoints = 100;
float notFov = 600;
float zStart = 20;
Vector3 basePos = Vector3(0, -5, 0);

void render()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  CV::clear(0.8, 0.8, 1);
  renderPistonCapsule();
  renderPiston();
  renderCrank();
  Sleep(1 / 100.0 * 1000.0);
}

void renderPistonCapsule()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(10, 2);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = translateZ(p, zStart);
    saida[i] = projeta(p, notFov);
  }
  CV::color(1, 0, 0);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

void renderPiston()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(10, 1.5);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = translateZ(p, zStart);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0, 1);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

void renderCrank()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getSidewaysCilinder(10, 1.5);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = translateZ(p, zStart);
    p = translateX(p, -10);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0.5, 0);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

Vector3 rotateY(Vector3 p, float ang)
{
  Vector3 r;
  r.x = p.x * cos(ang) - p.z * sin(ang);
  r.y = p.y;
  r.z = p.x * sin(ang) + p.z * cos(ang);
  return r;
}

Vector3 translateZ(Vector3 p, float d)
{
  Vector3 r;
  r.x = p.x;
  r.y = p.y;
  r.z = p.z + d;
  return r;
}

Vector3 translateX(Vector3 p, float d)
{
  Vector3 r;
  r.x = p.x + d;
  r.y = p.y;
  r.z = p.z;
  return r;
}

Vector3 translateY(Vector3 p, float d)
{
  Vector3 r;
  r.x = p.x;
  r.y = p.y + d;
  r.z = p.z;
  return r;
}

Vector2 projeta(Vector3 p, float d)
{
  Vector2 r;
  r.x = p.x * d / p.z;
  r.y = p.y * d / p.z;
  return r;
}

Vector3 *getCilinderPoints(float height, float raio)
{
  Vector3 *p = (Vector3 *)malloc(sizeof(Vector3) * totalPoints);
  float angulo = 0;
  for (int i = 0; i < totalPoints / 2; i++)
  {
    angulo = i * (2 * PI / (totalPoints / 2));
    float x = raio * cos(angulo) + basePos.x;
    float z = raio * sin(angulo) + basePos.z;
    p[i] = Vector3(x, basePos.y, z);
    p[i + totalPoints / 2] = Vector3(x, basePos.y + height, z);
  }
  return p;
}

Vector3 *getSidewaysCilinder(float height, float raio)
{
  Vector3 *p = (Vector3 *)malloc(sizeof(Vector3) * totalPoints);
  float angulo = 0;
  for (int i = 0; i < totalPoints / 2; i++)
  {
    angulo = i * (2 * PI / (totalPoints / 2));
    float z = raio * cos(angulo) + basePos.z;
    float y = raio * sin(angulo) + basePos.y;
    p[i] = Vector3(basePos.x, y, z);
    p[i + totalPoints / 2] = Vector3(basePos.x + height, y, z);
  }
  return p;
}

void drawCilinder(Vector2 *p)
{
  for (int i = 0; i < totalPoints / 2; i++)
  {
    int nextIndex = (i + 1) % (totalPoints / 2);
    CV::line(p[i].x, p[i].y, p[nextIndex].x, p[nextIndex].y);
    CV::line(p[i + totalPoints / 2].x, p[i + totalPoints / 2].y, p[nextIndex + totalPoints / 2].x, p[nextIndex + totalPoints / 2].y);
    CV::line(p[i].x, p[i].y, p[i + totalPoints / 2].x, p[i + totalPoints / 2].y);
  }
}

void keyboard(int key)
{
  if (key == 'w')
  {
    basePos.y += 1;
  }
  else if (key == 's')
  {
    basePos.y -= 1;
  }
  else if (key == 'a')
  {
    basePos.x += 1;
  }
  else if (key == 'd')
  {
    basePos.x -= 1;
  }
  else if (key == 201)
  {
    notFov += 10;
  }
  else if (key == 203)
  {
    notFov -= 10;
  }
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
  CV::init(screenWidth, screenHeight, "Trab4PedroRamos");
  CV::run();
}
