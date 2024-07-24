#include <GL/gl.h>
#include "Vector3.h"
#include <GL/glu.h>
#include "RefinedTetrahedron.h"

enum TreeType
{
  CUBE,
  PYRAMID,
  TETRAHEDRON,
};

class Tree
{
public:
  Tree(Vector3 position, TreeType type)
  {
    this->position = position;
    this->type = type;
    refinedTetrahedron.makeSubdivisions(3);
  }

  void render()
  {
    float cilinderHeight = 4.0f;
    srand(static_cast<unsigned int>(time(0)));
    glPushMatrix();
    glTranslatef(position.x, position.y + cilinderHeight, position.z);
    if (type == CUBE)
      renderCube();
    else if (type == PYRAMID)
      renderPyramid();
    else if (type == TETRAHEDRON)
      refinedTetrahedron.render();
    renderCylinder(0.5f, cilinderHeight, 30, 30);
    glPopMatrix();
  }

private:
  Vector3 position;
  TreeType type;
  RefinedTetrahedron refinedTetrahedron;
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
    glNormal3f(0.0, 1.0, 0.0);
    renderFrontFace();
    renderBackFace();
    renderLeftFace();
    renderRightFace();
    renderTopFace();
    renderBottomFace();
    glEnd();
    glPopMatrix();
  }
  Vector3 calculateNormal(Vector3 &A, Vector3 &B, Vector3 &C)
  {
    Vector3 u = B - A;
    Vector3 v = C - A;
    Vector3 normal = u.cross(v);
    normal.normalize();
    return normal;
  }

  void renderPyramid()
  {
    GLfloat vertices[] = {
        -1.0f, 0.0f, -1.0f, // 0
        1.0f, 0.0f, -1.0f,  // 1
        1.0f, 0.0f, 1.0f,   // 2
        -1.0f, 0.0f, 1.0f,  // 3
        0.0f, 1.0f, 0.0f    // 4 (tip)
    };

    GLubyte baseIndices[] = {
        0, 1, 2,
        0, 2, 3};

    GLubyte faceIndices[] = {
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4};

    Vector3 v0(vertices[0], vertices[1], vertices[2]);
    Vector3 v1(vertices[3], vertices[4], vertices[5]);
    Vector3 v2(vertices[6], vertices[7], vertices[8]);
    Vector3 v3(vertices[9], vertices[10], vertices[11]);
    Vector3 v4(vertices[12], vertices[13], vertices[14]);

    Vector3 normal;

    glPushMatrix();
    glScalef(2.0, 5.0, 2.0);

    glBegin(GL_TRIANGLES);

    glColor3f(0.0, 1.0, 0.0);
    normal = calculateNormal(v2, v1, v0);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(v0.x, v0.y, v0.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);

    glVertex3f(v0.x, v0.y, v0.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);

    normal = calculateNormal(v4, v1, v0);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(v0.x, v0.y, v0.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v4.x, v4.y, v4.z);

    normal = calculateNormal(v4, v2, v1);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v4.x, v4.y, v4.z);

    normal = calculateNormal(v4, v3, v2);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);

    normal = calculateNormal(v4, v0, v3);
    glNormal3f(normal.x, normal.y, normal.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v0.x, v0.y, v0.z);
    glVertex3f(v4.x, v4.y, v4.z);

    glEnd();
    glPopMatrix();
  }
  void renderFrontFace()
  {
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
  }

  void renderBackFace()
  {
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
  }

  void renderLeftFace()
  {
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
  }

  void renderRightFace()
  {
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
  }

  void renderTopFace()
  {
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
  }

  void renderBottomFace()
  {
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
  }
};
