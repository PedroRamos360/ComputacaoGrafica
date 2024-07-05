#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vector3.h"
#include "./Vector2.h"

#include "gl_canvas2d.h"
int screenWidth = 1200, screenHeight = 800;

struct GearPoints
{
  Vector3 *firstGear;
  Vector3 *secondGear;
};

Vector3 rotateY(Vector3 p, float ang, Vector3 center = Vector3(0, 0, 0));
Vector3 rotateZ(Vector3 p, float ang, Vector3 center = Vector3(0, 0, 0));
Vector3 rotateX(Vector3 p, float ang, Vector3 center = Vector3(0, 0, 0));
Vector3 translateZ(Vector3 p, float d);
Vector3 translateX(Vector3 p, float d);
Vector3 translateY(Vector3 p, float d);
Vector2 projeta(Vector3 p, float d);
void drawGear(Vector2 *p);
void drawCilinder(Vector2 *p);
Vector3 *getCilinderPoints(float height, float raio);
Vector3 *getSidewaysCilinder(float height, float raio);
Vector3 *getGearPoints(float z);
void renderPistonCapsule();
void renderPiston();
void renderMovingCrank();
void renderCrankIntersection();
void renderMainCrank();
void renderMainGear();
void renderAuxiliarGear();

int totalPoints = 100;
float notFov = 600;
float zStart = 40;
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
float pistonTranslateY = -19;
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
  renderMainGear();
  renderAuxiliarGear();
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

bool shouldDrawVec(Vector3 p, bool shouldDraw)
{
  if (!shouldDraw)
    return false;
  return p.z > 0;
}

void renderPistonCapsule()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(smallHeight, bigRadius);
  Vector3 pistonStartPoint = Vector3(0, smallHeight, 0);
  Vector3 pistonDirection = movingCrankCenter - pistonStartPoint;
  pistonDirection.normalize();
  float angle = acos(pistonDirection.dotProduct(Vector3(0, 0, 1)));
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, angle - PI / 2, Vector3(0, smallHeight, 0));
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = projeta(p, notFov);
  }
  CV::color(1, 0, 0);
  if (shouldDraw)
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

int pistonDir = -1;
void renderPiston()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(bigHeight, smallRadius);
  Vector3 pistonStartPoint = Vector3(0, smallHeight, 0);
  Vector3 pistonDirection = movingCrankCenter - pistonStartPoint;
  pistonDirection.normalize();
  float angle = acos(pistonDirection.dotProduct(Vector3(0, 0, 1)));
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, angle - PI / 2, Vector3(0, smallHeight - pistonTranslateY, 0));
    p = pistonVecOperations(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0, 1);
  pistonTranslateY = movingCrankCenter.y - 2;
  if (shouldDraw)
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
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = movingCrankVecOperations(p, crankSize);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = projeta(p, notFov);
  }
  movingCrankCenter = movingCrankVecOperations(movingCrankCenter, crankSize);
  mainRotation += 0.01f;
  CV::color(0, 0.5, 0);
  if (shouldDraw)
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
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, mainRotation, Vector3(0, (baseCrankSize + smallRadius), 0));
    p = translateX(p, -crankSize - smallRadius * 2);
    p = translateY(p, crankYTranslation);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0.5, 0.5);
  if (shouldDraw)
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
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = rotateX(p, mainRotation);
    p = translateX(p, -crankSize - smallRadius - baseCrankSize);
    p = translateY(p, smallRadius + baseCrankSize + crankYTranslation);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0.5, 0.5, 0);
  if (shouldDraw)
    drawCilinder(saida);
  free(saida);
  free(entrada);
}

int baseGearPoints = (totalPoints * 2);
int gearPoints = baseGearPoints - (baseGearPoints % 4);
int lastLineOffset = 4;
int offsetToNextGear = gearPoints + lastLineOffset;

Vector3 gearTransformations(Vector3 p, int rotationDir = 1)
{
  float angToAdd = 0;
  if (rotationDir == -1)
    angToAdd = (2 * PI) / (gearPoints / 2);
  p = rotateY(p, PI / 2, Vector3(0, 0, 0));
  p = rotateX(p, mainRotation * rotationDir + angToAdd, Vector3(0, 0, 0));
  p = translateX(p, -25);
  p = translateY(p, smallRadius + baseCrankSize + crankYTranslation);
  return p;
}

void renderMainGear()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints * 6);
  Vector3 *entrada = getGearPoints(1);
  bool shouldDraw = true;
  for (int i = 0; i < offsetToNextGear * 2; i++)
  {
    p = entrada[i];
    p = gearTransformations(p);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, true);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0.5, 0.5);
  if (shouldDraw)
  {
    drawGear(saida);
  }
  free(saida);
  free(entrada);
}

void renderAuxiliarGear()
{
  Vector3 p;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints * 6);
  Vector3 *entrada = getGearPoints(1);
  bool shouldDraw = true;
  for (int i = 0; i < offsetToNextGear * 2; i++)
  {
    p = entrada[i];
    p = gearTransformations(p, -1);
    p = translateZ(p, 11);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, true);
    saida[i] = projeta(p, notFov);
  }
  CV::color(0, 0.5, 0.5);
  if (shouldDraw)
  {
    drawGear(saida);
  }
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

Vector3 *getGearPoints(float height)
{
  printf("\nGearPoints: %d", gearPoints);
  Vector3 *p = (Vector3 *)malloc(sizeof(Vector3) * offsetToNextGear * 2);
  float raio1 = 5, raio2 = 6, ang = 0;
  float raio = raio1;
  float innerCircleRadius = 5;
  float lastInnerX = innerCircleRadius * cos(ang);
  float lastInnerY = innerCircleRadius * sin(ang);
  float lastX = raio1 * cos(ang);
  float lastY = raio1 * sin(ang);
  float passo = (2 * PI) / (gearPoints / 2);
  int i = 0;
  for (ang; ang <= 2 * PI + passo; ang += passo)
  {
    float x1 = raio * cos(ang);
    float y1 = raio * sin(ang);
    float innerX = innerCircleRadius * cos(ang);
    float innerY = innerCircleRadius * sin(ang);
    ang += passo;
    float innerX2 = innerCircleRadius * cos(ang);
    float innerY2 = innerCircleRadius * sin(ang);
    float x2 = raio * cos(ang);
    float y2 = raio * sin(ang);
    p[i] = Vector3(x1, y1, 0);
    p[i + 1] = Vector3(x2, y2, 0);
    p[i + 2] = Vector3(lastX, lastY, 0);
    p[i + 3] = Vector3(x1, y1, 0);
    p[i + offsetToNextGear] = Vector3(x1, y1, height);
    p[i + 1 + offsetToNextGear] = Vector3(x2, y2, height);
    p[i + 2 + offsetToNextGear] = Vector3(lastX, lastY, height);
    p[i + 3 + offsetToNextGear] = Vector3(x1, y1, height);
    // CV::line(innerX, innerY, innerX2, innerY2);
    // CV::line(lastInnerX, lastInnerY, innerX, innerY);
    lastInnerX = innerX2;
    lastInnerY = innerY2;
    lastX = x2;
    lastY = y2;
    if (raio == raio1)
      raio = raio2;
    else
      raio = raio1;

    i += 4;
  }
  return p;
}

void drawGear(Vector2 *p)
{
  for (int i = 0; i < offsetToNextGear; i += 2)
  {
    int nextIndex = i + 1;
    CV::line(p[i].x, p[i].y, p[nextIndex].x, p[nextIndex].y);
    CV::line(p[i + offsetToNextGear].x, p[i + offsetToNextGear].y, p[nextIndex + offsetToNextGear].x, p[nextIndex + offsetToNextGear].y);
    if (p[i + offsetToNextGear].x == 0 || p[i + offsetToNextGear].y == 0)
      continue;
    CV::line(p[i].x, p[i].y, p[i + offsetToNextGear].x, p[i + offsetToNextGear].y);
  }
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
