#include "Vector3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class KeyboardManager
{
private:
  float *cameraRotation;
  float *rpmControl;
  Vector3 *basePos;
  float moveSpeed = 1.0f;

public:
  KeyboardManager(float *cameraRotation, float *rpmControl, Vector3 *basePos)
  {
    this->cameraRotation = cameraRotation;
    this->rpmControl = rpmControl;
    this->basePos = basePos;
  }

  void handleKeyStroke(int key)
  {
    switch (key)
    {
    case 'w':
      basePos->y -= moveSpeed;
      break;
    case 's':
      basePos->y += moveSpeed;
      break;
    case 'a':
      basePos->x += moveSpeed * cos(*cameraRotation);
      basePos->z -= moveSpeed * sin(*cameraRotation);
      break;
    case 'd':
      basePos->x -= moveSpeed * cos(*cameraRotation);
      basePos->z += moveSpeed * sin(*cameraRotation);
      break;
    case 'm':
      *rpmControl += 0.01f;
      break;
    case 'n':
      *rpmControl -= 0.01f;
      break;
    case 201:
      basePos->x -= moveSpeed * sin(*cameraRotation);
      basePos->z -= moveSpeed * cos(*cameraRotation);
      break;
    case 203:
      basePos->x += moveSpeed * sin(*cameraRotation);
      basePos->z += moveSpeed * cos(*cameraRotation);
      break;
    case 200:
      *cameraRotation -= 0.1f;
      break;
    case 202:
      *cameraRotation += 0.1f;
      break;
    }
  }
};