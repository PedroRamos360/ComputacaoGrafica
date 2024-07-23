#include <GL/gl.h>
#include "Vector3.h"
#include <GL/glu.h>

enum TreeType
{
  CUBE,
  PYRAMID
};

class Tree
{
public:
  Tree(Vector3 position, TreeType type)
  {
    this->position = position;
    this->type = type;
  }

  void render()
  {
    float cilinderHeight = 4.0f;
    srand(static_cast<unsigned int>(time(0)));
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslatef(position.x, position.y + cilinderHeight, position.z);
    switch (type)
    {
    case CUBE:
      renderCube();
      break;
    case PYRAMID:
      renderPyramid();
      break;
    }
    renderCylinder(0.5f, cilinderHeight, 30, 30);
    glPopMatrix();
  }

private:
  Vector3 position;
  TreeType type;
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
    glPushMatrix();
    glScalef(1.0, 2.0, 1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    renderFrontFace();
    renderBackFace();
    renderLeftFace();
    renderRightFace();
    renderTopFace();
    renderBottomFace();
    glEnd();
    glPopMatrix();
  }

  void renderPyramid()
  {
    GLfloat vertices[] = {
        -1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    GLubyte baseIndices[] = {
        0, 1, 2,
        0, 2, 3};
    GLubyte faceIndices[] = {
        0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};
    glPushMatrix();
    glScalef(2.0, 5.0, 2.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColor3f(0.0, 1.0, 0.0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, baseIndices);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, faceIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
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
