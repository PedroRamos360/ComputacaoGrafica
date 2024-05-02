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

void rotateSquare(Vector2 square[], double angle)
{
  double angleRad = angle * PI / 180.0;
  for (int i = 0; i < 4; ++i)
  {
    double newX = cos(angleRad) * square[i].x - sin(angleRad) * square[i].y;
    double newY = sin(angleRad) * square[i].x + cos(angleRad) * square[i].y;
    square[i].x = newX;
    square[i].y = newY;
  }
}

void questao3_2020_2(Square *square)
{
  translateRect(-l / 2 - x, -l / 2 - y, square);
  scale(-30, square);
  rotateSquare(square->points, 45);
}

void questao4_2019_1(Square *square)
{

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
  questao3_2020_2(square);
  renderSquare(square);
  renderSquare(&originalSquare);
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
