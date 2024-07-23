#include <GL/gl.h>
#include "Vector3.h"
#include <GL/glu.h>

class Tree
{
public:
  Tree(Vector3 position)
  {
    this->position = position;
  }

  void render()
  {
    float cilinderHeight = 4.0f;
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslatef(position.x, position.y + 3.0, position.z);
    renderCube();
    renderCylinder(0.5f, cilinderHeight, 30, 30);
    glPopMatrix();
  }

private:
  Vector3 position;
  void renderCylinder(float radius, float height, int slices, int stacks)
  {
    glPushMatrix();
    glRotatef(90.0f, 1.0, 0.0, 0.0);
    glColor3f(0.588f, 0.294f, 0.0f);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
    gluCylinder(quadratic, radius, radius, height, slices, stacks);
    gluDeleteQuadric(quadratic);
    glPopMatrix();
  }

  void renderCube()
  {
    glTranslatef(position.x, position.y, position.z);
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    renderFrontFace();
    renderBackFace();
    renderLeftFace();
    renderRightFace();
    renderTopFace();
    renderBottomFace();
    glEnd();
  }

  void renderFrontFace()
  {
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
  }

  void renderBackFace()
  {
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
  }

  void renderLeftFace()
  {
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
  }

  void renderRightFace()
  {
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
  }

  void renderTopFace()
  {
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
  }

  void renderBottomFace()
  {
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
  }
};
