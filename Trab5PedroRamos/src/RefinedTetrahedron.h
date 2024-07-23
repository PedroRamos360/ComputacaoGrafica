#include <vector>
#include <GLFW/glfw3.h>
#include <GL/glcorearb.h>
#include <GL/glu.h>
#include <vector>

using namespace std;

struct Face
{
  Vector3 a, b, c;
};

class RefinedTetrahedron
{
public:
  RefinedTetrahedron()
  {
  }

  void makeSubdivisions(int subdivisions)
  {
    for (int i = 0; i < subdivisions; i++)
    {
      facesToRender = subdivide(facesToRender);
    }
  }

  void render()
  {
    glPushMatrix();
    glScalef(2.0, 2.0, 2.0);
    glTranslatef(0, 0.5, 0);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);
    for (Face face : facesToRender)
    {
      renderFace(face);
    }

    glEnd();
    glPopMatrix();
  }

private:
  vector<Vector3> basePoints = {
      Vector3(1, 0, -1 / sqrt(2)),
      Vector3(-1, 0, -1 / sqrt(2)),
      Vector3(0, 1, 1 / sqrt(2)),
      Vector3(0, -1, 1 / sqrt(2))};
  vector<Face> facesToRender = {
      {basePoints[0], basePoints[1], basePoints[2]},
      {basePoints[0], basePoints[1], basePoints[3]},
      {basePoints[0], basePoints[2], basePoints[3]},
      {basePoints[1], basePoints[2], basePoints[3]}};

  Vector3 midpoint(const Vector3 &a, const Vector3 &b)
  {
    return Vector3((a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f, (a.z + b.z) / 2.0f);
  }

  vector<Face> subdivide(const vector<Face> &faces)
  {
    vector<Face> newFaces;
    for (auto face : faces)
    {
      Vector3 ab = midpoint(face.a, face.b);
      Vector3 bc = midpoint(face.b, face.c);
      Vector3 ca = midpoint(face.c, face.a);
      ab.normalize();
      bc.normalize();
      ca.normalize();
      face.a.normalize();
      face.b.normalize();
      face.c.normalize();

      newFaces.push_back({face.a, ab, ca});
      newFaces.push_back({face.b, bc, ab});
      newFaces.push_back({face.c, ca, bc});
      newFaces.push_back({ab, bc, ca});
    }
    return newFaces;
  }

  void renderFace(Face face)
  {
    glVertex3f(face.a.x, face.a.y, face.a.z);
    glVertex3f(face.b.x, face.b.y, face.b.z);
    glVertex3f(face.c.x, face.c.y, face.c.z);
  }
};
