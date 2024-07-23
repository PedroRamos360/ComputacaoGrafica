#include <GL/gl.h>
#include <cmath>

class SceneLight
{
public:
  SceneLight() {}

  void startLighting()
  {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat light_diffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  }
  void setPosition(float x, float y, float z, float w = 0.0f)
  {
    GLfloat light_position[] = {x, y, z, w};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  }
};
