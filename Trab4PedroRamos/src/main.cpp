#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vector3.h"
#include "./Vector2.h"
#include "./KeyboardManager.h"

#include "gl_canvas2d.h"
int screenWidth = 1200, screenHeight = 800;

void drawGear(Vector2 *p);
void drawCilinder(Vector2 *p);
Vector3 *getCilinderPoints(float height, float raio, bool isSideways = false);
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
Vector3 basePos = Vector3(0, 0, 0);

float bigRadius = 2;
float smallRadius = 1.5;
float crankYTranslation = -19;
float baseCrankSize = 8;
float cameraRotation = 0;
float pistonYDirection = -1;
float virabrequimRadius = smallRadius + baseCrankSize;
float bigHeight = virabrequimRadius * 2;
float smallHeight = bigHeight - smallRadius * 2;
float pistonTranslateY = -19;
Vector3 movingCrankCenter = Vector3(0, 0, 0);
float rpmControl = 0.01f;
float mainRotation = 0;
KeyboardManager keyboardManager = KeyboardManager(&cameraRotation, &rpmControl, &basePos);

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
}

Vector3 baseTransform(Vector3 p)
{
  p = p.translateZ(zStart);
  p = p.translateX(basePos.x);
  p = p.translateY(basePos.y);
  p = p.translateZ(basePos.z);
  p = p.rotateY(cameraRotation);
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
    p = p.rotateX(angle - PI / 2, Vector3(0, smallHeight, 0));
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = p.project(notFov);
  }
  CV::color(1, 0, 0);
  if (shouldDraw)
    drawCilinder(saida);
  free(saida);
  free(entrada);
}

Vector3 pistonVecOperations(Vector3 p)
{
  p = p.translateY(pistonTranslateY);
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
    p = p.rotateX(angle - PI / 2, Vector3(0, smallHeight - pistonTranslateY, 0));
    p = pistonVecOperations(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = p.project(notFov);
  }
  CV::color(0, 0, 1);
  pistonTranslateY = movingCrankCenter.y - 2;
  if (shouldDraw)
    drawCilinder(saida);
  free(saida);
  free(entrada);
}

Vector3 movingCrankVecOperations(Vector3 p, float crankSize)
{
  p = p.rotateX(mainRotation, Vector3(0, baseCrankSize, 0));
  p = p.translateX(-crankSize - smallRadius);
  p = p.translateY(smallRadius + crankYTranslation);
  return p;
}

void renderMovingCrank()
{
  Vector3 p;
  float crankSize = baseCrankSize;
  Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * totalPoints);
  Vector3 *entrada = getCilinderPoints(crankSize, smallRadius, true);
  movingCrankCenter = Vector3(crankSize, 0, 0);
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = movingCrankVecOperations(p, crankSize);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = p.project(notFov);
  }
  movingCrankCenter = movingCrankVecOperations(movingCrankCenter, crankSize);
  mainRotation += rpmControl;
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
    p = p.rotateX(mainRotation, Vector3(0, (baseCrankSize + smallRadius), 0));
    p = p.translateX(-crankSize - smallRadius * 2);
    p = p.translateY(crankYTranslation);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = p.project(notFov);
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
  Vector3 *entrada = getCilinderPoints(crankSize, smallRadius, true);
  bool shouldDraw = true;
  for (int i = 0; i < totalPoints; i++)
  {
    p = entrada[i];
    p = p.rotateX(mainRotation);
    p = p.translateX(-crankSize - smallRadius - baseCrankSize);
    p = p.translateY(smallRadius + baseCrankSize + crankYTranslation);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, shouldDraw);
    saida[i] = p.project(notFov);
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
  p = p.rotateY(PI / 2, Vector3(0, 0, 0));
  p = p.rotateX(mainRotation * rotationDir + angToAdd, Vector3(0, 0, 0));
  p = p.translateX(-25);
  p = p.translateY(smallRadius + baseCrankSize + crankYTranslation);
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
    saida[i] = p.project(notFov);
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
    p = p.translateZ(11);
    p = baseTransform(p);
    shouldDraw = shouldDrawVec(p, true);
    saida[i] = p.project(notFov);
  }
  CV::color(0, 0.5, 0.5);
  if (shouldDraw)
  {
    drawGear(saida);
  }
  free(saida);
  free(entrada);
}

Vector3 *getCilinderPoints(float height, float raio, bool isSideways)
{
  Vector3 *p = (Vector3 *)malloc(sizeof(Vector3) * totalPoints);
  float angulo = 0;
  for (int i = 0; i < totalPoints / 2; i++)
  {
    angulo = i * (2 * PI / (totalPoints / 2));
    if (isSideways)
    {
      float z = raio * cos(angulo);
      float y = raio * sin(angulo);
      p[i] = Vector3(0, y, z);
      p[i + totalPoints / 2] = Vector3(height, y, z);
    }
    else
    {
      float x = raio * cos(angulo);
      float z = raio * sin(angulo);
      p[i] = Vector3(x, 0, z);
      p[i + totalPoints / 2] = Vector3(x, height, z);
    }
  }
  return p;
}

Vector3 *getGearPoints(float height)
{
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
  keyboardManager.handleKeyStroke(key);
}

void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
}

int main(void)
{
  CV::init(screenWidth, screenHeight, "Trab4PedroRamos");
  CV::run();
}
