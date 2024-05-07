/* Classe que renderiza os blocos na tela e tem funções para reduzir a vida e buscar as vidas
de um bloco específico*/

#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <iostream>
#include "../gl_canvas2d.h"
#include "../Vector2.h"
#include <random>

#define BLOCK_SIZE 50

using namespace std;

class Block
{
private:
  int lives;

public:
  float x, y;
  int size = BLOCK_SIZE;
  Block(float x, float y, int lives);
  void render();
  void decreaseLife();
  int getLives();
};

#endif // BLOCK_H