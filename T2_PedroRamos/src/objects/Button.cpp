#include "Button.h"

using namespace std;

Button::Button(float x, float y, float height, string label, function<void()> onClick)
    : x(x), y(y), height(height), label(label), onClick(onClick)
{
  this->width = label.size() * 11;
}
void Button::Render()
{
  CV::color(0, 1, 0);
  CV::rectFill(x, y, x + width, y + height);
  CV::color(0, 0, 0);
  CV::text(x + label.size() / 1.5, y + height / 2, label.c_str());
}

bool Button::handleColision(int mouseX, int mouseY)
{
  if (mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + height))
  {
    onClick();
    return true;
  }
  return false;
}