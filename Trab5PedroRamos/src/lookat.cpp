/*
Trabalho 5 - Pedro Ramos

Requisitos básicos desenvolvidos:
- Todos requisitos básicos foram implementados

Requisitos extras desenvolvidos:
- Uso de texturas no terreno
- Imagem responsiva a diferentes tamanhos de tela

Controles de teclado (também inclusos no console):
- W: Move para frente
- S: Move para trás
- A: Move para a esquerda
- D: Move para a direita
- Q: Move para baixo
- E: Move para cima
- Setas direcionais: Rotacionam a câmera
- K: Troca de wireframe para preenchimento de polígonos e vice-versa
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "Camera.h"
#include "KeyboardManager.h"
#include <vector>
#include "TreeGenerator.h"
#include "Floor.h"
#include "SceneLight.h"
#include <GL/wglext.h>

#define SCREEN_X 800
#define SCREEN_Y 600

using namespace std;

Camera camera;
KeyboardManager *KeyboardManager::instance = nullptr;
HeightMap heightMap;
TreeGenerator treeGenerator(heightMap);
Floor floorRenderer(heightMap);
SceneLight sceneLight;

void init()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.8, 0.8, 1, 1);
  glEnable(GL_DEPTH_TEST);
  sceneLight.startLighting();
  floorRenderer.loadTexture();
}

void MouseFunc(int button, int state, int x, int y)
{
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  KeyboardManager *keyboardManager = KeyboardManager::getInstance(&camera);
  keyboardManager->processInput();
  gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, 0, 1, 0);

  floorRenderer.render();
  treeGenerator.renderTrees();
  sceneLight.setPosition(1.0f, 1.0f, 1.0f, 0.0f);

  glFlush();
  glutSwapBuffers();
}

void resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, static_cast<float>(width) / height, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
}

void vSync()
{
  PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
  if (wglSwapIntervalEXT)
  {
    wglSwapIntervalEXT(1);
  }
}

int main()
{
  int argc = 0;
  glutInit(&argc, NULL);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(SCREEN_X, SCREEN_Y);
  glutInitWindowPosition(450, 10);
  glutCreateWindow("Trab5PedroRamos");
  init();
  vSync();

  glutDisplayFunc(display);
  glutMouseFunc(MouseFunc);
  glutIdleFunc(display);
  glutReshapeFunc(resize);

  glutMainLoop();
  return 0;
}
