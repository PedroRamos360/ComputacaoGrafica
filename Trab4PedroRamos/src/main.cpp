#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vector3.h"
#include "./Vector2.h"

#include "gl_canvas2d.h"
int screenWidth = 1200, screenHeight = 800;

Vector3 rotateY(Vector3 p, float ang, Vector3 center = Vector3(0, 0, 0));
Vector3 rotateZ(Vector3 p, float ang, Vector3 center = Vector3(0, 0, 0));
Vector3 rotateX(Vector3 p, float ang, Vector3 center = Vector3(0, 0, 0));
Vector3 translateZ(Vector3 p, float d);
Vector3 translateX(Vector3 p, float d);
Vector3 translateY(Vector3 p, float d);
Vector2 projeta(Vector3 p, float d);
void drawCilinder(Vector2 *p);
Vector3 *getCilinderPoints(float height, float raio);
Vector3 *getSidewaysCilinder(float height, float raio);
void renderPistonCapsule();
void renderPiston();
void renderMovingCrank();
void renderCrankIntersection();
void renderMainCrank();

int totalPoints = 100;
float notFov = 400;
float zStart = 20;
// Vector3 basePos = Vector3(35.835564, 1, -20.321634);
Vector3 basePos = Vector3(0, 0, 0);

float bigRadius = 2;
float smallRadius = 1.5;
float crankYTranslation = -19;
float baseCrankSize = 8;
// float cameraRotation = 1.7;
float cameraRotation = 0;
float pistonYDirection = -1;
float virabrequimRadius = smallRadius + baseCrankSize;
float bigHeight = virabrequimRadius * 2;
float smallHeight = bigHeight - smallRadius * 2;
float pistonTranslateY = smallHeight - bigHeight;
Vector3 movingCrankCenter = Vector3(0, 0, 0);

void render()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  CV::clear(0.8, 0.8, 1);
  renderMovingCrank();
  renderPistonCapsule();
  renderPiston();
  renderCrankIntersection();
  renderMainCrank();
  Sleep(1 / 100.0 * 1000.0);
}

Vector3 baseTransform(Vector3 p)
{
  p = translateZ(p, zStart);
  p = translateX(p, basePos.x);
  p = translateY(p, basePos.y);
  p = translateZ(p, basePos.z);
  p = rotateY(p, cameraRotation);
  return p;
}

void renderPistonCapsule()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(smallHeight, bigRadius);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = baseTransform(p);
    saida[i] = projeta(p, notFov);
  }
  CV::color(1, 0, 0);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

Vector3 pistonVecOperations(Vector3 p)
{
  p = translateY(p, pistonTranslateY);
  p = baseTransform(p);
  return p;
}

void renderPiston()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(bigHeight, smallRadius);
  Vector3 pistonStartPoint = Vector3(0, bigHeight, 0);
  Vector3 pistonDirection = movingCrankCenter - pistonStartPoint;
  pistonDirection.normalize();
  float angle = acos(pistonDirection.dotProduct(Vector3(0, 0, 1)));
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, angle - PI / 2, Vector3(0, bigHeight, 0));
    p = pistonVecOperations(p);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0, 1);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

float mainRotation = 0;

Vector3 movingCrankVecOperations(Vector3 p, float crankSize)
{
  p = rotateX(p, mainRotation, Vector3(0, baseCrankSize, 0));
  p = translateX(p, -crankSize - smallRadius);
  p = translateY(p, smallRadius + crankYTranslation);
  return p;
}

void renderMovingCrank()
{
  Vector3 p;
  float crankSize = baseCrankSize;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getSidewaysCilinder(crankSize, smallRadius);
  movingCrankCenter = Vector3(crankSize, 0, 0);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = movingCrankVecOperations(p, crankSize);
    p = baseTransform(p);
    saida[i] = projeta(p, notFov);
  }
  movingCrankCenter = movingCrankVecOperations(movingCrankCenter, crankSize);
  mainRotation += 0.01f;
  CV::color(0, 0.5, 0);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

void renderCrankIntersection()
{
  Vector3 p;
  float crankSize = baseCrankSize;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(crankSize, smallRadius);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, mainRotation, Vector3(0, (baseCrankSize + smallRadius), 0));
    p = translateX(p, -crankSize - smallRadius * 2);
    p = translateY(p, crankYTranslation);
    p = baseTransform(p);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0.5, 0.5);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

void renderMainCrank()
{
  Vector3 p;
  float crankSize = 15;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getSidewaysCilinder(crankSize, smallRadius);
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, mainRotation);
    p = translateX(p, -crankSize - smallRadius - baseCrankSize);
    p = translateY(p, smallRadius + baseCrankSize + crankYTranslation);
    p = baseTransform(p);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0.5, 0.5, 0);
  drawCilinder(saida);
  free(saida);
  free(entrada);
}

Vector3 rotateY(Vector3 p, float ang, Vector3 center)
{
  Vector3 r;
  p.x -= center.x;
  p.y -= center.y;
  p.z -= center.z;
  r.x = p.x * cos(ang) - p.z * sin(ang);
  r.y = p.y;
  r.z = p.x * sin(ang) + p.z * cos(ang);
  r.x += center.x;
  r.y += center.y;
  r.z += center.z;
  return r;
}

Vector3 rotateZ(Vector3 p, float ang, Vector3 center)
{
  Vector3 r;
  p.x -= center.x;
  p.y -= center.y;
  p.z -= center.z;
  r.x = p.x * cos(ang) - p.y * sin(ang);
  r.y = p.x * sin(ang) + p.y * cos(ang);
  r.z = p.z;
  r.x += center.x;
  r.y += center.y;
  r.z += center.z;
  return r;
}

Vector3 rotateX(Vector3 p, float ang, Vector3 center)
{
  Vector3 r;
  p.x -= center.x;
  p.y -= center.y;
  p.z -= center.z;
  r.x = p.x;
  r.y = p.y * cos(ang) - p.z * sin(ang);
  r.z = p.y * sin(ang) + p.z * cos(ang);
  r.x += center.x;
  r.y += center.y;
  r.z += center.z;
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
    float x = raio * cos(angulo);
    float z = raio * sin(angulo);
    p[i] = Vector3(x, 0, z);
    p[i + totalPoints / 2] = Vector3(x, height, z);
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
    float z = raio * cos(angulo);
    float y = raio * sin(angulo);
    p[i] = Vector3(0, y, z);
    p[i + totalPoints / 2] = Vector3(height, y, z);
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
  float moveSpeed = 1.0f;

  if (key == 'w')
  {
    basePos.y -= moveSpeed;
  }
  else if (key == 's')
  {
    basePos.y += moveSpeed;
  }
  else if (key == 'a')
  {
    basePos.x += moveSpeed * cos(cameraRotation);
    basePos.z -= moveSpeed * sin(cameraRotation);
  }
  else if (key == 'd')
  {
    basePos.x -= moveSpeed * cos(cameraRotation);
    basePos.z += moveSpeed * sin(cameraRotation);
  }
  else if (key == 201)
  {
    basePos.x -= moveSpeed * sin(cameraRotation);
    basePos.z -= moveSpeed * cos(cameraRotation);
  }
  else if (key == 203)
  {
    basePos.x += moveSpeed * sin(cameraRotation);
    basePos.z += moveSpeed * cos(cameraRotation);
  }
  else if (key == 200)
  {
    cameraRotation -= 0.1f;
  }
  else if (key == 202)
  {
    cameraRotation += 0.1f;
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
