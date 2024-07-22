#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

class Piston2D
{
private:
  Vector2 rectangle[4] = {
      Vector2(-10, -125),
      Vector2(-40, -125),
      Vector2(-40, -135),
      Vector2(-10, -135)};

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

  void gear(float angInit, bool isMain = false)
  {
    float raio1 = 100, raio2 = 120, ang = 0;
    float passo = (2 * PI) / 80;
    if (isMain)
    {
      angInit = -(angInit - passo);
      CV::translate(screenWidth / 2 - 50 + 220, screenHeight / 2 - 130);
    }
    else
    {
      CV::translate(screenWidth / 2 - 50, screenHeight / 2 - 130);
    }
    float raio = raio1;
    float innerCircleRadius = 50;
    float lastX = raio1 * cos(ang + angInit);
    float lastY = raio1 * sin(ang + angInit);
    for (ang; ang <= 2 * PI + passo; ang += passo)
    {
      float x1 = raio * cos(ang + angInit);
      float y1 = raio * sin(ang + angInit);
      float innerX = innerCircleRadius * cos(ang + angInit);
      float innerY = innerCircleRadius * sin(ang + angInit);
      ang += passo;
      float innerX2 = innerCircleRadius * cos(ang + angInit);
      float innerY2 = innerCircleRadius * sin(ang + angInit);
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

public:
  void show2DPiston(float rotationSpeed)
  {
    CV::translate(screenWidth / 2, screenHeight / 2);
    Vector2 newRotatedAxis = drawPistonAxis();
    newRotatedAxis = rotate(newRotatedAxis, PI / 2, blackAxis);
    drawMetalBar(newRotatedAxis);
    drawOrangeBar(newRotatedAxis);
    drawMetalAxis();
    drawMiddleAxisBar();
    gear(angInit);
    gear(angInit, true);
    angInit += rotationSpeed;
  }
};
