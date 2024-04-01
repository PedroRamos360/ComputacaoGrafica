#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "../gl_canvas2d.h"
#include <iostream>
#include <string.h>
#include "Image.h"
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
  void handleColision(int mouseX, int mouseY);
};

#endif
