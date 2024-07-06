#include "./Vector3.h"
#include "./Vector2.h"
#include "./Prism.h"
#include "./BaseTransformer.h"

class GearsManager
{
private:
  int *totalPoints;
  float *mainRotation;
  float *smallRadius;
  float *baseCrankSize;
  float *crankYTranslation;
  float *notFov;
  BaseTransformer *baseTransformer;

  int baseGearPoints;
  int gearPoints;
  int lastLineOffset;
  int offsetToNextGear;

  void initialize()
  {
    baseGearPoints = (*totalPoints * 2);
    gearPoints = baseGearPoints - (baseGearPoints % 4);
    lastLineOffset = 4;
    offsetToNextGear = gearPoints + lastLineOffset;
  }

  Vector3 *getGearPoints(float height)
  {
    Vector3 *p = (Vector3 *)malloc(sizeof(Vector3) * offsetToNextGear * 2);
    float raio1 = 5, raio2 = 6, ang = 0;
    float raio = raio1;
    float innerCircleRadius = 5;
    float lastInnerX = innerCircleRadius * cos(ang);
    float lastInnerY = innerCircleRadius * sin(ang);
    float lastX = raio1 * cos(ang);
    float lastY = raio1 * sin(ang);
    float passo = (2 * PI) / (gearPoints / 2);
    int i = 0;
    for (ang; ang <= 2 * PI + passo; ang += passo)
    {
      float x1 = raio * cos(ang);
      float y1 = raio * sin(ang);
      float innerX = innerCircleRadius * cos(ang);
      float innerY = innerCircleRadius * sin(ang);
      ang += passo;
      float innerX2 = innerCircleRadius * cos(ang);
      float innerY2 = innerCircleRadius * sin(ang);
      float x2 = raio * cos(ang);
      float y2 = raio * sin(ang);
      p[i] = Vector3(x1, y1, 0);
      p[i + 1] = Vector3(x2, y2, 0);
      p[i + 2] = Vector3(lastX, lastY, 0);
      p[i + 3] = Vector3(x1, y1, 0);
      p[i + offsetToNextGear] = Vector3(x1, y1, height);
      p[i + 1 + offsetToNextGear] = Vector3(x2, y2, height);
      p[i + 2 + offsetToNextGear] = Vector3(lastX, lastY, height);
      p[i + 3 + offsetToNextGear] = Vector3(x1, y1, height);
      lastInnerX = innerX2;
      lastInnerY = innerY2;
      lastX = x2;
      lastY = y2;
      if (raio == raio1)
        raio = raio2;
      else
        raio = raio1;

      i += 4;
    }
    return p;
  }
  Vector3 gearTransformations(Vector3 p, int rotationDir = 1)
  {
    float angToAdd = 0;
    if (rotationDir == -1)
      angToAdd = (2 * PI) / (gearPoints / 2);
    p = p.rotateY(PI / 2, Vector3(0, 0, 0));
    p = p.rotateX(*mainRotation * rotationDir + angToAdd, Vector3(0, 0, 0));
    p = p.translateX(-25);
    p = p.translateY(*smallRadius + *baseCrankSize + *crankYTranslation);
    return p;
  }
  void renderMainGear()
  {
    Vector3 p;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints * 6);
    Vector3 *entrada = getGearPoints(1);
    bool shouldDraw = true;
    for (int i = 0; i < offsetToNextGear * 2; i++)
    {
      p = entrada[i];
      p = gearTransformations(p);
      p = baseTransformer->transform(p);
      shouldDraw = p.shouldDrawVec(true);
      saida[i] = p.project(*notFov);
    }
    CV::color(0, 0.5, 0.5);
    if (shouldDraw)
    {
      Prism::draw(saida, offsetToNextGear, 2);
    }
    free(saida);
    free(entrada);
  }

  void renderAuxiliarGear()
  {
    Vector3 p;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints * 6);
    Vector3 *entrada = getGearPoints(1);
    bool shouldDraw = true;
    for (int i = 0; i < offsetToNextGear * 2; i++)
    {
      p = entrada[i];
      p = gearTransformations(p, -1);
      p = p.translateZ(11);
      p = baseTransformer->transform(p);
      shouldDraw = p.shouldDrawVec(true);
      saida[i] = p.project(*notFov);
    }
    CV::color(0, 0.5, 0.5);
    if (shouldDraw)
    {
      Prism::draw(saida, offsetToNextGear, 2);
    }
    free(saida);
    free(entrada);
  }

public:
  GearsManager(int *totalPoints, float *mainRotation, float *smallRadius, float *baseCrankSize, float *crankYTranslation, float *notFov, BaseTransformer *baseTransformer)
  {
    this->totalPoints = totalPoints;
    this->mainRotation = mainRotation;
    this->smallRadius = smallRadius;
    this->baseCrankSize = baseCrankSize;
    this->crankYTranslation = crankYTranslation;
    this->notFov = notFov;
    this->baseTransformer = baseTransformer;
    initialize();
  }

  void renderGears()
  {
    renderMainGear();
    renderAuxiliarGear();
  }
};