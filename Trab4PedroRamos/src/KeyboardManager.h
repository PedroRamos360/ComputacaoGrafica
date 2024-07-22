/* Classe para executar ações de acordo com as teclas pressionadas pelo usuário:
 * w: move para cima
 * s: move para baixo
 * a: move para a esquerda
 * d: move para a direita
 * seta pra cima: move pra frente
 * seta pra baixo: move pra trás
 * m: aumenta a rotação do motor
 * n: diminui a rotação do motor
 * seta para esquerda e direita: gira a câmera
 * k: alterna entre pistão 2D e 3D
 */

#include "Vector3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class KeyboardManager
{
private:
  float *cameraRotation;
  float *rpmControl;
  bool *show2DPiston;
  Vector3 *basePos;
  float moveSpeed = 1.0f;

public:
  KeyboardManager(float *cameraRotation, float *rpmControl, Vector3 *basePos, bool *show2DPiston)
  {
    this->cameraRotation = cameraRotation;
    this->rpmControl = rpmControl;
    this->basePos = basePos;
    this->show2DPiston = show2DPiston;
    printf("Esquema de botoes do teclado:\nw: move para cima\ns: move para baixo\na: move para a esquerda\nd: move para a direita\nseta pra cima: move pra frente\nseta pra baixo: move pra tras\nm: aumenta a rotacao do motor\nn: diminui a rotacao do motor\nseta para esquerda e direita: gira a camera\nk: alterna entre pistão 2D e 3D\n");
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
    case 'k':
      *show2DPiston = !*show2DPiston;
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