// Classe responsável por calcular e renderizar todos os cilindros da cena

class CilinderManager
{
private:
  int *totalPoints;
  float *notFov, *smallRadius, *crankYTranslation, *baseCrankSize, *rpmControl, *mainRotation;
  float pistonTranslateY;
  float bigHeight;
  float smallHeight;
  float bigRadius;
  BaseTransformer *baseTransformer;
  Vector3 movingCrankCenter;

  void initialize()
  {
    pistonTranslateY = -19;
    float virabrequimRadius = *smallRadius + *baseCrankSize;
    bigHeight = virabrequimRadius * 2;
    smallHeight = bigHeight - *smallRadius * 2;
    movingCrankCenter = Vector3(0, 0, 0);
    bigRadius = 2;
  }

  Vector3 pistonVecOperations(Vector3 p)
  {
    p = p.translateY(pistonTranslateY);
    p = baseTransformer->transform(p);
    return p;
  }

  Vector3 movingCrankVecOperations(Vector3 p, float crankSize)
  {
    p = p.rotateX(*mainRotation, Vector3(0, *baseCrankSize, 0));
    p = p.translateX(-crankSize - *smallRadius);
    p = p.translateY(*smallRadius + *crankYTranslation);
    return p;
  }

  Vector3 *getCilinderPoints(float height, float raio, bool isSideways = false)
  {
    Vector3 *p = (Vector3 *)malloc(sizeof(Vector3) * *totalPoints);
    float angulo = 0;
    for (int i = 0; i < *totalPoints / 2; i++)
    {
      angulo = i * (2 * PI / (*totalPoints / 2));
      if (isSideways)
      {
        float z = raio * cos(angulo);
        float y = raio * sin(angulo);
        p[i] = Vector3(0, y, z);
        p[i + *totalPoints / 2] = Vector3(height, y, z);
      }
      else
      {
        float x = raio * cos(angulo);
        float z = raio * sin(angulo);
        p[i] = Vector3(x, 0, z);
        p[i + *totalPoints / 2] = Vector3(x, height, z);
      }
    }
    return p;
  }

public:
  CilinderManager(int *totalPoints, float *notFov, float *smallRadius, float *crankYTranslation, float *baseCrankSize, float *rpmControl, float *mainRotation, BaseTransformer *baseTransformer)
  {
    this->totalPoints = totalPoints;
    this->notFov = notFov;
    this->smallRadius = smallRadius;
    this->crankYTranslation = crankYTranslation;
    this->baseCrankSize = baseCrankSize;
    this->rpmControl = rpmControl;
    this->mainRotation = mainRotation;
    this->baseTransformer = baseTransformer;
    initialize();
  }

  void renderPistonCapsule()
  {
    Vector3 p;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints);
    Vector3 *entrada = getCilinderPoints(smallHeight, bigRadius);
    Vector3 pistonStartPoint = Vector3(0, smallHeight, 0);
    Vector3 pistonDirection = movingCrankCenter - pistonStartPoint;
    pistonDirection.normalize();
    float angle = acos(pistonDirection.dotProduct(Vector3(0, 0, 1)));
    bool shouldDraw = true;
    for (int i = 0; i < *totalPoints; i++)
    {
      p = entrada[i];
      p = p.rotateX(angle - PI / 2, Vector3(0, smallHeight, 0));
      p = baseTransformer->transform(p);
      shouldDraw = p.shouldDrawVec(shouldDraw);
      saida[i] = p.project(*notFov);
    }
    CV::color(1, 0, 0);
    if (shouldDraw)
      Prism::draw(saida, *totalPoints / 2, 1);
    free(saida);
    free(entrada);
  }

  void renderPiston()
  {
    Vector3 p;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints);
    Vector3 *entrada = getCilinderPoints(bigHeight, *smallRadius);
    Vector3 pistonStartPoint = Vector3(0, smallHeight, 0);
    Vector3 pistonDirection = movingCrankCenter - pistonStartPoint;
    pistonDirection.normalize();
    float angle = acos(pistonDirection.dotProduct(Vector3(0, 0, 1)));
    bool shouldDraw = true;
    for (int i = 0; i < *totalPoints; i++)
    {
      p = entrada[i];
      p = p.rotateX(angle - PI / 2, Vector3(0, smallHeight - pistonTranslateY, 0));
      p = pistonVecOperations(p);
      shouldDraw = p.shouldDrawVec(shouldDraw);
      saida[i] = p.project(*notFov);
    }
    CV::color(0, 0, 1);
    pistonTranslateY = movingCrankCenter.y - 2;
    if (shouldDraw)
      Prism::draw(saida, *totalPoints / 2, 1);
    free(saida);
    free(entrada);
  }

  void renderMovingCrank()
  {
    Vector3 p;
    float crankSize = *baseCrankSize;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints);
    Vector3 *entrada = getCilinderPoints(crankSize, *smallRadius, true);
    movingCrankCenter = Vector3(crankSize, 0, 0);
    bool shouldDraw = true;
    for (int i = 0; i < *totalPoints; i++)
    {
      p = entrada[i];
      p = movingCrankVecOperations(p, crankSize);
      p = baseTransformer->transform(p);
      shouldDraw = p.shouldDrawVec(shouldDraw);
      saida[i] = p.project(*notFov);
    }
    movingCrankCenter = movingCrankVecOperations(movingCrankCenter, crankSize);
    *mainRotation += *rpmControl;
    CV::color(0, 0.5, 0);
    if (shouldDraw)
      Prism::draw(saida, *totalPoints / 2, 1);
    free(saida);
    free(entrada);
  }

  void renderCrankIntersection()
  {
    Vector3 p;
    float crankSize = *baseCrankSize;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints);
    Vector3 *entrada = getCilinderPoints(crankSize, *smallRadius);
    bool shouldDraw = true;
    for (int i = 0; i < *totalPoints; i++)
    {
      p = entrada[i];
      p = p.rotateX(*mainRotation, Vector3(0, (*baseCrankSize + *smallRadius), 0));
      p = p.translateX(-crankSize - *smallRadius * 2);
      p = p.translateY(*crankYTranslation);
      p = baseTransformer->transform(p);
      shouldDraw = p.shouldDrawVec(shouldDraw);
      saida[i] = p.project(*notFov);
    }
    CV::color(0, 0.5, 0.5);
    if (shouldDraw)
      Prism::draw(saida, *totalPoints / 2, 1);
    free(saida);
    free(entrada);
  }

  void renderMainCrank()
  {
    Vector3 p;
    float crankSize = 15;
    Vector2 *saida = (Vector2 *)malloc(sizeof(Vector2) * *totalPoints);
    Vector3 *entrada = getCilinderPoints(crankSize, *smallRadius, true);
    bool shouldDraw = true;
    for (int i = 0; i < *totalPoints; i++)
    {
      p = entrada[i];
      p = p.rotateX(*mainRotation);
      p = p.translateX(-crankSize - *smallRadius - *baseCrankSize);
      p = p.translateY(*smallRadius + *baseCrankSize + *crankYTranslation);
      p = baseTransformer->transform(p);
      shouldDraw = p.shouldDrawVec(shouldDraw);
      saida[i] = p.project(*notFov);
    }
    CV::color(0.5, 0.5, 0);
    if (shouldDraw)
      Prism::draw(saida, *totalPoints / 2, 1);
    free(saida);
    free(entrada);
  }
};