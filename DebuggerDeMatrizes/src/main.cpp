#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix3x3.h"
#include "Vector2.h"
#include <array>

#include "gl_canvas2d.h"
using namespace std;

int screenWidth = 500, screenHeight = 500;

struct Square
{
  Vector2 points[4];
};

float x = 150, y = 100;
float l = 100;
float alfa;
Matrix3x3 mainMatrix;

Square square = {
    Vector2(x, y),
    Vector2(x + l, y),
    Vector2(x + l, y + l),
    Vector2(x, y + l)};

void renderAxis()
{
  CV::line(-screenWidth / 2, 0, screenWidth / 2, 0);
  CV::line(0, -screenHeight / 2, 0, screenHeight / 2);
}

void renderSquare(Square square)
{
  for (int i = 0; i < 4; i++)
  {
    if (i == 3)
      CV::line(square.points[3].x, square.points[3].y, square.points[0].x, square.points[0].y);
    else
      CV::line(square.points[i].x, square.points[i].y, square.points[i + 1].x, square.points[i + 1].y);
  }
}

Square applyMatrixToSquare(Square square, Matrix3x3 M)
{
  Square newSquare;
  for (int i = 0; i < 4; i++)
  {
    Vector2 point = square.points[i];
    Vector2 newPoint = Vector2(M.matrix[0][0] * point.x + M.matrix[0][1] * point.y + M.matrix[0][2],
                               M.matrix[1][0] * point.x + M.matrix[1][1] * point.y + M.matrix[1][2]);
    newSquare.points[i] = newPoint;
  }
  return newSquare;
}

void render()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  CV::line(0, 0, x, y);
  CV::color(0, 0, 0);
  renderSquare(square);
  renderAxis();
  Square newSquare = applyMatrixToSquare(square, mainMatrix);
  CV::color(1, 0, 0);
  renderSquare(newSquare);
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
  Vector2 P = Vector2(x, y);
  P.normalize();
  Vector2 Q = Vector2(1, 0);
  alfa = acos(P * Q);
  Matrix3x3 E = Matrix3x3({{{0.6, 0, 0},
                            {0, 0.6, 0},
                            {0, 0, 1}}});
  Matrix3x3 R = Matrix3x3({{{cos(alfa), -sin(alfa), 0},
                            {sin(alfa), cos(alfa), 0},
                            {0, 0, 1}}});
  Matrix3x3 T1 = Matrix3x3({{{1, 0, -x},
                             {0, 1, -y},
                             {0, 0, 1}}});
  Matrix3x3 T2 = Matrix3x3({{{1, 0, x},
                             {0, 1, y},
                             {0, 0, 1}}});

  square = applyMatrixToSquare(square, T2 * R * T1);
  R = Matrix3x3({{{cos(-alfa), -sin(-alfa), 0},
                  {sin(-alfa), cos(-alfa), 0},
                  {0, 0, 1}}});
  mainMatrix = T2 * R * E * T1;
  CV::init(screenWidth, screenHeight, "Teste");
  CV::run();
}
