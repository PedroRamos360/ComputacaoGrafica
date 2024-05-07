/* Simplesmente renderiza a tela final de gameover junto com o botão de reset, não conhece a implementação
do click do reset, isso está declarado na clase Camp que passa como parâmetro para cá*/

#include "../gl_canvas2d.h"
#include <string>
#include <iostream>
#include "Button.h"

using namespace std;

#define PIXELS_BY_CHAR 10

class Gameover
{
private:
  float x, y;
  int *screenHeight, *screenWidth, finalScore;
  Button *resetButton;

public:
  Gameover(int *screenHeight, int *screenWidth, int finalScore, function<void()> onClickReset)
  {
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    this->finalScore = finalScore;
    this->resetButton = new Button(*this->screenWidth / 2 - 20, *this->screenHeight / 2 - 20, 20, "Reset", onClickReset);
  }

  void render()
  {
    CV::translate(*this->screenWidth / 2, *this->screenHeight / 2);
    CV::color(1, 0, 0);
    string gameOver = "Game Over";
    int xGameOver = gameOver.length() / 2 * PIXELS_BY_CHAR;
    CV::text(-xGameOver, 40, gameOver.c_str());
    CV::color(0, 0, 0);
    string score = "Pontuação: " + to_string(this->finalScore);
    int xScore = score.length() / 2 * PIXELS_BY_CHAR;
    CV::text(-xScore, 20, score.c_str());
    CV::translate(0, 0);
    this->resetButton->Render();
  }

  bool handleResetClick(int mouseX, int mouseY)
  {
    return this->resetButton->handleColision(mouseX, mouseY);
  }
};
