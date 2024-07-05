#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
int screenWidth = 500, screenHeight = 500;

Vector2 rectangle[4] = {
    Vector2(-10, -125),
    Vector2(-40, -125),
    Vector2(-40, -135),
    Vector2(-10, -135)};

void drawRect(Vector2 *rectangle)
{
  for (int i = 0; i < 4; i++)
  {
    int next = (i + 1) % 4;
    CV::line(rectangle[i], rectangle[next]);
  }
}

Vector2 rotate(Vector2 vec, float angle, Vector2 center)
{
  float transX = vec.x - center.x;
  float transY = vec.y - center.y;
  float xnew = transX * cos(angle) - transY * sin(angle);
  float ynew = transX * sin(angle) + transY * cos(angle);
  return Vector2(xnew + center.x, ynew + center.y);
}

Vector2 *rotateRect(Vector2 *rect, float angle, Vector2 center = Vector2(0, 0))
{
  Vector2 *newRect = (Vector2 *)malloc(4 * sizeof(Vector2));
  for (int i = 0; i < 4; i++)
  {
    newRect[i] = rotate(rect[i], angle, center);
  }
  return newRect;
}

float angInit = 0;
Vector2 rotationAxis = Vector2(-50, -130);
Vector2 rotatedAxis = Vector2(0, -130);
Vector2 blackAxis = Vector2(0, 25);
float metalBarLength = 100;
float baseMetalBarY = -100 + blackAxis.y;
Vector2 baseMetalBar[4] = {
    Vector2(-5, baseMetalBarY),
    Vector2(5, baseMetalBarY),
    Vector2(5, baseMetalBarY - metalBarLength),
    Vector2(-5, baseMetalBarY - metalBarLength)};
Vector2 baseOrangeBar[4] = {
    Vector2(-10, 0 + blackAxis.y),
    Vector2(10, 0 + blackAxis.y),
    Vector2(10, -100 + blackAxis.y),
    Vector2(-10, -100 + blackAxis.y)};

float distanceBetweenVectors(Vector2 a, Vector2 b)
{
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void drawMetalBar(Vector2 newRotatedAxis)
{
  Vector2 blackAxisToRotatedAxis = newRotatedAxis - blackAxis;
  blackAxisToRotatedAxis.normalize();
  float angle = atan2(blackAxisToRotatedAxis.y, blackAxisToRotatedAxis.x);
  float distance = distanceBetweenVectors(blackAxis, newRotatedAxis);
  Vector2 scaledMetalBar[4];
  for (int i = 0; i < 4; i++)
  {
    float newY = baseMetalBar[i].y - distance + 212;
    scaledMetalBar[i] = Vector2(baseMetalBar[i].x, newY);
  }
  Vector2 *newMetalBar = rotateRect(scaledMetalBar, angle, blackAxis);
  CV::color(0.5, 0.5, 0.5);
  drawRect(newMetalBar);
}

void drawOrangeBar(Vector2 newRotatedAxis)
{

  Vector2 blackAxisToRotatedAxis = newRotatedAxis - blackAxis;
  blackAxisToRotatedAxis.normalize();
  float angle = atan2(blackAxisToRotatedAxis.y, blackAxisToRotatedAxis.x);
  Vector2 *newOrangeBar = rotateRect(baseOrangeBar, angle, blackAxis);
  CV::color(1, 0.8, 0);
  drawRect(newOrangeBar);
}

void drawMetalAxis()
{
  CV::color(0, 0, 0);
  CV::circleFill(blackAxis, 7, 20);
}

Vector2 drawPistonAxis()
{
  CV::circle(rotate(rotatedAxis, angInit, rotationAxis), 10, 20);
  CV::circle(rotationAxis, 10, 20);
  return rotate(rotatedAxis, angInit, rotationAxis);
}

void drawMiddleAxisBar()
{
  CV::color(0, 0, 0);
  Vector2 *newRect = rotateRect(rectangle, angInit, rotationAxis);
  drawRect(newRect);
}

void render()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  Vector2 newRotatedAxis = drawPistonAxis();
  newRotatedAxis = rotate(newRotatedAxis, PI / 2, blackAxis);
  drawMetalBar(newRotatedAxis);
  drawOrangeBar(newRotatedAxis);
  drawMetalAxis();
  drawMiddleAxisBar();
  angInit += 1 / 100.0;
  Sleep(1 / 400.0 * 1000);
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
  CV::init(screenWidth, screenHeight, "Trab 4 - Pedro Ramos");
  CV::run();
}
