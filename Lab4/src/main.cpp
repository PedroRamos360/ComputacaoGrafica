/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2024
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "gl_canvas2d.h"

struct Square
{
  Vector2 points[4];
};

int screenWidth = 500, screenHeight = 500;

int opcao = 50;     // variavel global para selecao do que sera exibido na canvas.
int mouseX, mouseY; // variaveis globais do mouse para poder exibir dentro da render().
float x = 100;
float y = 100;
float l = 100;
Square originalSquare = {
    Vector2(x, y),
    Vector2(x + l, y),
    Vector2(x + l, y + l),
    Vector2(x, y + l)};

void translateRect(float dx, float dy, Square *square)
{
  for (int i = 0; i < 4; i++)
  {
    square->points[i].x += dx;
    square->points[i].y += dy;
  }
}

void scale(float inc, Square *square)
{
  square->points[0].x -= inc / 2;
  square->points[0].y -= inc / 2;
  square->points[1].x += inc / 2;
  square->points[1].y -= inc / 2;
  square->points[2].x += inc / 2;
  square->points[2].y += inc / 2;
  square->points[3].x -= inc / 2;
  square->points[3].y += inc / 2;
}

void scaleMultiply(float scale, Square *square)
{
  for (int i = 0; i < 4; i++)
  {
    square->points[i].x *= scale;
    square->points[i].y *= scale;
  }
}

void rotateSquare(Vector2 square[], double angle)
{
  for (int i = 0; i < 4; ++i)
  {
    double newX = cos(angle) * square[i].x - sin(angle) * square[i].y;
    double newY = sin(angle) * square[i].x + cos(angle) * square[i].y;
    square[i].x = newX;
    square[i].y = newY;
  }
}

void renderSquare(Square *square)
{
  for (int i = 0; i < 4; i++)
  {
    if (i == 3)
      CV::line(square->points[3].x, square->points[3].y, square->points[0].x, square->points[0].y);
    else
      CV::line(square->points[i].x, square->points[i].y, square->points[i + 1].x, square->points[i + 1].y);
  }
}

void questao3_2020_2(Square *square)
{
  translateRect(-l / 2 - x, -l / 2 - y, square);
  CV::color(1, 0, 0);
  renderSquare(square);
  scale(-30, square);
  CV::color(0, 1, 0);
  renderSquare(square);
  rotateSquare(square->points, PI / 4);
  CV::color(0, 0, 1);
  renderSquare(square);
}

void questao4_2019_1(Square *square)
{
  translateRect(-x, -y, square);
  CV::color(1, 0, 0);
  renderSquare(square);
  scaleMultiply(0.6666666f, square);
  CV::color(0, 1, 0);
  renderSquare(square);
  float newL = l * 0.6666666f;
  translateRect(-newL / 2, 0, square);
  CV::color(0, 0, 1);
  renderSquare(square);
  Vector2 dirXYSquare = Vector2(x, y + l);
  dirXYSquare.normalize();
  Vector2 xAxisVector = Vector2(1, 0);
  float angle = acos(dirXYSquare * xAxisVector);
  rotateSquare(square->points, angle);
  CV::color(1, 0, 1);
  renderSquare(square);
  translateRect(x, y + l, square);
  CV::color(0, 1, 1);
  renderSquare(square);
}

void renderAxis()
{
  CV::line(-screenWidth / 2, 0, screenWidth / 2, 0);
  CV::line(0, -screenHeight / 2, 0, screenHeight / 2);
}

void render()
{
  CV::color(0, 0, 0);
  CV::translate(screenWidth / 2, screenHeight / 2);
  renderAxis();
  Square *square = (Square *)malloc(sizeof(Square));
  *square = originalSquare;
  renderSquare(&originalSquare);
  questao4_2019_1(square);
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
  CV::init(screenWidth, screenHeight, "Canvas");
  CV::run();
}
