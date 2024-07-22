#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./Vector3.h"
#include "./Vector2.h"
#include "./KeyboardManager.h"
#include "./GearsManager.h"
#include "gl_canvas2d.h"
#include "CilinderManager.h"
#include "./Piston2D.h"

int screenWidth = 1200, screenHeight = 800;
int totalPoints = 100;
float notFov = 600;
float zStart = 40;
Vector3 basePos = Vector3(0, 0, 0);
float smallRadius = 1.5;
float crankYTranslation = -19;
float baseCrankSize = 8;
float cameraRotation = 0;
float rpmControl = 0.01f;
float mainRotation = 0;
bool show2DPiston = false;
KeyboardManager keyboardManager = KeyboardManager(&cameraRotation, &rpmControl, &basePos, &show2DPiston);
BaseTransformer baseTransformer = BaseTransformer(&zStart, &basePos, &cameraRotation);
GearsManager gearsManager = GearsManager(&totalPoints, &mainRotation, &smallRadius, &baseCrankSize, &crankYTranslation, &notFov, &baseTransformer);
CilinderManager cilinderManager = CilinderManager(&totalPoints, &notFov, &smallRadius, &crankYTranslation, &baseCrankSize, &rpmControl, &mainRotation, &baseTransformer);
Piston2D piston2D = Piston2D();

void render()
{
  CV::translate(screenWidth / 2, screenHeight / 2);
  CV::clear(0.8, 0.8, 1);
  if (show2DPiston)
  {
    piston2D.show2DPiston(rpmControl);
  }
  else
  {
    cilinderManager.renderMovingCrank();
    cilinderManager.renderPiston();
    cilinderManager.renderPistonCapsule();
    cilinderManager.renderCrankIntersection();
    cilinderManager.renderMainCrank();
    gearsManager.renderMainGear();
    gearsManager.renderAuxiliarGear();
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
