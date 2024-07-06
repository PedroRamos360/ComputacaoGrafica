#include "Vector3.h"
class BaseTransformer
{
private:
  float *zStart;
  Vector3 *basePos;
  float *cameraRotation;

public:
  BaseTransformer(float *zStart, Vector3 *basePos, float *cameraRotation)
  {
    this->zStart = zStart;
    this->basePos = basePos;
    this->cameraRotation = cameraRotation;
  }

  Vector3 transform(Vector3 p)
  {
    p = p.translateZ(*zStart);
    p = p.translateX(basePos->x);
    p = p.translateY(basePos->y);
    p = p.translateZ(basePos->z);
    p = p.rotateY(*cameraRotation);
    return p;
  }
};