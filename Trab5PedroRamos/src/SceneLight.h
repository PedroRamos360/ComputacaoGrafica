#include <GL/gl.h>
#include <cmath>

class SceneLight
{
public:
  SceneLight()
  {
  }

  void updatePosition(float angle)
  {
    float radius = 40.0f;
    float x = radius * cos(angle);
    float z = radius * sin(angle);
    float y = 3.0f;
    setPosition(x, y, z);
  }

  void startLighting()
  {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  }

private:
  void setPosition(float x, float y, float z, float w = 1.0f)
  {
    GLfloat light_position[] = {x, y, z, w};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  }
};
