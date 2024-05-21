#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"
int screenWidth = 500, screenHeight = 500;

float j30(float t)
{
  return (1 - t) * (1 - t) * (1 - t);
}

float j31(float t)
{
  return 3 * t * (1 - t) * (1 - t);
}

float j32(float t)
{
  return 3 * t * t * (1 - t);
}

float j33(float t)
{
  return t * t * t;
}

void renderBezierPolynomials()
{
  float scale = 200;
  CV::translate(screenWidth / 2 - scale / 2, screenHeight / 2 - scale / 2);
  for (float i = 0; i <= 1; i += 0.001)
  {
    CV::color(1, 0, 0);
    CV::point(i * scale, j30(i) * scale);
    CV::color(0, 1, 0);
    CV::point(i * scale, j31(i) * scale);
    CV::color(0, 0, 1);
    CV::point(i * scale, j32(i) * scale);
    CV::color(1, 0, 1);
    CV::point(i * scale, j33(i) * scale);
  }
}

/*(1-t)3
 (valor máximo em t=0)
3t(1-t)2 (valor máximo em t=1/3)
3t2
(1-t) (valor máximo em t=2/3)
t
*/

Vector2 calculateBezierPoint(float t, Vector2 cps[4])
{
  Vector2 output = cps[0] * j30(t) + cps[1] * j31(t) + cps[2] * j32(t) + cps[3] * j33(t);
  return output;
}

void renderBezierCurve(Vector2 controlPoints[4])
{
  for (int i = 0; i < 3; i++)
  {
    CV::color(0.7, 0.7, 0.7);
    CV::line(controlPoints[i].x, controlPoints[i].y, controlPoints[i + 1].x, controlPoints[i + 1].y);
    CV::color(0, 0, 0);
    CV::circleFill(controlPoints[i].x, controlPoints[i].y, 3, 50);
  }
  CV::circleFill(controlPoints[3].x, controlPoints[3].y, 3, 50);
  for (float t = 0; t <= 1; t += 0.001)
  {
    CV::point(calculateBezierPoint(t, controlPoints));
  }
}

Vector2 controlPoints[4] = {Vector2(100, 100), Vector2(200, 200), Vector2(300, 100), Vector2(400, 200)};

void render()
{
  renderBezierCurve(controlPoints);
}

void keyboard(int key)
{
  printf("\nTecla: %d", key);
}

void keyboardUp(int key)
{
  printf("\nLiberou: %d", key);
}

bool toggleMouseHold = false;

int getIndexOfClosestControlPoint(int mouseX, int mouseY)
{
  int smallestDiff = abs(controlPoints[0].x - mouseX) + abs(controlPoints[0].y - mouseY);
  int index = 0;
  for (int i = 1; i < 4; i++)
  {
    int diff = abs(controlPoints[i].x - mouseX) + abs(controlPoints[i].y - mouseY);
    if (diff < smallestDiff)
    {
      smallestDiff = diff;
      index = i;
    }
  }
  return index;
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  if (state == 0)
    toggleMouseHold = !toggleMouseHold;
  if (toggleMouseHold)
  {
    controlPoints[getIndexOfClosestControlPoint(x, y)] = Vector2(x, y);
  }
}

int main(void)
{
  CV::init(screenWidth, screenHeight, "Lab5");
  CV::run();
}
