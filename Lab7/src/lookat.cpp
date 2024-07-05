/**
*   Programa para ilustrar:
*   - Uso da gluLookAt
*   - Pilha de transformacoes
*   - Projecao pespectiva
*   - Interacao com o mouse/teclado
*   - cullFace, frontFace

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "Vector2.h"

#define SCREEN_X 500
#define SCREEN_Y 500

int polygonMode = 1;

float rotateX = 0, rotateZ = 0;

float abertura = 20.0;
float znear = 1;
float zfar = 23;
float aspect = 1;

void init()
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(abertura, aspect, znear, zfar);
  glMatrixMode(GL_MODELVIEW);

  glClearColor(0, 0, 0, 1);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glEnable(GL_DEPTH_TEST);
}

// imprime as matrizes da pilha do opengl
void printMatrix(GLenum pname)
{
  GLfloat m[16]; // usado para leitura das matrizes
  glGetFloatv(pname, m);
  int l, c;
  for (l = 0; l < 4; l++)
  {
    for (c = 0; c < 4; c++)
    {
      int pos = l * 4 + c;
    }
  }
}

void bule1()
{
  glPushMatrix();
  glColor3f(1, 0, 1);
  glTranslated(-0.5, 0.15, 0.5);
  glutWireTeapot(0.2);
  glPopMatrix();
}

void bule2()
{
  glPushMatrix();
  glColor3f(0, 1, 0);
  glTranslated(0.5, 0.15, -0.5);
  glRotated(90, 0, 1, 0);
  glutWireTeapot(0.2);
  glPopMatrix();
}

void bule3()
{
  glColor3f(0, 0, 1);
  glutSolidTeapot(1.2);
}

void drawTriangle()
{
  glColor3f(1, 0, 0); // Red color for the triangle
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.5, 0, -1);
  glVertex3f(0.5, 0, -1);
  glVertex3f(0, 1, -1);
  glEnd();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  printMatrix(GL_PROJECTION_MATRIX);

  gluPerspective(abertura, aspect, znear, zfar);

  printMatrix(GL_MODELVIEW_MATRIX);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  gluLookAt(0, 0, 15, // from. Posicao onde a camera esta posicionada
            0, 0, 0,  // to. Posicao absoluta onde a camera esta vendo
            0, 1, 0); // up. Vetor Up.

  glRotatef((GLfloat)rotateX, 0.0f, 1.0f, 0.0f);
  glRotatef((GLfloat)rotateZ, 1.0f, 0.0f, 0.0f);

  // todos os objetos estao definidos na origem do sistema global fixo
  // e sao transladados para a posicao destino.
  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  glVertex3f(-1, 0, 1);
  glVertex3f(1, 0, 1);
  glVertex3f(1, 0, -1);
  glVertex3f(-1, 0, -1);
  glEnd();

  bule1();
  bule2();
  bule3();
  drawTriangle();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  key = tolower(key);
  switch (key)
  {
  case 27:
    exit(0);
    break;

  case 'w':
    if (polygonMode == 1)
    {
      polygonMode = 0;
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
      polygonMode = 1;
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    break;
  case '+':
    abertura += 1;
    break;
  case '-':
    abertura -= 1;
    break;
  }
}

void MotionFunc(int x, int y)
{
  rotateX = x;
  rotateZ = y;
}

void MouseFunc(int botao, int estado, int x, int y)
{
}

int main()
{
  int argc = 0;
  glutInit(&argc, NULL);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(SCREEN_X, SCREEN_Y);
  glutInitWindowPosition(450, 10);
  glutCreateWindow("GluLookAt Demo");
  init();
  printf("Digite W para mudar o modo de visualizacao: wireframe/fill");

  glutDisplayFunc(display);
  glutMotionFunc(MotionFunc);
  glutMouseFunc(MouseFunc);
  glutIdleFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}
