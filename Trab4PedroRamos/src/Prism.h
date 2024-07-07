// Classe para renderizar um prisma, uma linha renderiza a base de baixo, outra a base de cima e a outra liga os pontos da base de baixo com a de cima.

#include "Vector2.h"
#include "gl_canvas2d.h"

class Prism
{
public:
  static void draw(Vector2 *p, int size, int increment)
  {
    for (int i = 0; i < size; i += increment)
    {
      int nextIndex = (i + 1) % size;
      CV::line(p[i].x, p[i].y, p[nextIndex].x, p[nextIndex].y);
      CV::line(p[i + size].x, p[i + size].y, p[nextIndex + size].x, p[nextIndex + size].y);
      CV::line(p[i].x, p[i].y, p[i + size].x, p[i + size].y);
    }
  }
};