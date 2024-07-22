#include <GL/glut.h>

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define SCREEN_X 500
#define SCREEN_Y 500

struct InitProps
{
  float openness;
  float aspectRatio;
  float zNearDistance;
  float zFarDistance;
};

void init(InitProps initProps)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(initProps.openness, initProps.aspectRatio, initProps.zNearDistance, initProps.zFarDistance);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0, 0, 0, 1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);
}

void display(void)
{
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  }
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
  glutCreateWindow("Trab5PedroRamos");
  InitProps initProps;
  initProps.openness = 20.0;
  initProps.aspectRatio = 1.0;
  initProps.zNearDistance = 1.0;
  initProps.zFarDistance = 23.0;
  init(initProps);

  glutDisplayFunc(display);
  glutMouseFunc(MouseFunc);
  glutIdleFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}
