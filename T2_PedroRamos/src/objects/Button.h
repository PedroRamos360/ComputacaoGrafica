/*
Classe para renderizar todos os botões que aparecem na tela, recebe uma função lambda na propriedade
onClick que executa a lógica responsável pelo botão, dessa forma é possível manter a lógica de colisão
do botão generalizada dentro da classe e alterar só a funcionalidade de cada um dos botões.
*/

#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "../gl_canvas2d.h"
#include <iostream>
#include <string.h>
#include <thread>
#include <future>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <unistd.h>
using namespace std;

class Button
{
private:
  float height, width, x, y;
  function<void()> onClick;
  string label;

public:
  Button(float x, float y, float height, string label, function<void()> onClick);
  void Render();
  bool handleColision(int mouseX, int mouseY);
};

#endif
