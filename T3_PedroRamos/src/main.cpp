/*
Trabalho 3 - Computação Gráfica - Balls Bounce
Autor: Pedro Henrique Warken Ramos

Recursos implementados:
- Colisão de bola com bloco
- Colisão de bola com paredes
- Canhão que segue o mouse e dispara as bolas
- Aumento da dificuldade lineramente com o tempo:
  - A cada nível aumenta 1 vida dos novos blocos
  - A cada 10 níveis da um bônus de 10 vidas a mais para os novos blocos
- Geração de novos blocos de forma aleatória:
  - Sempre terá ao menos 1 bloco na nova linha
  - Depois disso é feito um rand em loop para adicionar mais 6 dígitos na string, 0 ou 1
  - Depois é feito um shuffle na string para embaralhar os bits e mostrar os blocos em posições aleatórias
  - A seed do rand é o tempo atual

- Limitação da amplitude do canhão:
  - Limitei o ângulo do canhão para não ter menos que 180 graus de amplitude porque pelos meus testes
  isso acabou tornando o jogo muito fácil e também muito lento
  - Se o canhão estiver mirado pra baixo não é mostrado, nem é possível disparar
  - Se o canhão estiver em um ângulo para cima mas que não é possível atirar ele fica vermelho
- Botão para puxar bolas restantes para baixo:
  - Caso demore muito para as bolas caírem é possível clicar flechinha pra baixo no teclado para
  que elas todas desçam de uma vez e passe por próximo nível para não ter que ficar esperando
  - Possui verificação de misclick: se o jogador acidentalmente clicar 2 vezes ele não vai passar 2 níveis
  diretamente porque é necessário que tenha algua bola na tela para que ele possa pular o nível

Recursos bônus implementados:
- Tela de gameover
  - Mostra a pontuação final
  - Botão de reset para recomeçar o nível do 0
*/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "objects/Camp.h"

#include "gl_canvas2d.h"

int screenWidth = 1280, screenHeight = 720;
int mouseX = 0, mouseY = 0;

Camp *camp = NULL;

void render()
{
  camp->render();
}

void keyboard(int key)
{
}

void keyboardUp(int key)
{
  if (key == 203)
  {
    camp->handleArrowDown();
  }
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
  mouseX = x;
  mouseY = y;
  if (state == 1)
  {
    camp->handleMouseClick();
  }
}

int main(void)
{
  camp = new Camp(&screenWidth, &screenHeight, &mouseX, &mouseY);
  CV::init(screenWidth, screenHeight, "Balls Bounce - Pedro Henrique Warken Ramos");
  CV::run();
}
