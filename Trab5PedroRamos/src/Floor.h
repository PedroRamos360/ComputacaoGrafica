#include <GL/gl.h>
#include "Vector3.h"
#include <vector>
#include <cmath>
#include "Bmp.h"
#include <string>
#include <GL/glcorearb.h>

using namespace std;

class Floor
{
private:
  string fileName = "Trab5PedroRamos/images/grass.bmp";
  vector<Vector3> points;
  vector<Vector3> normals;
  int gridWidth;
  int gridHeight;
  GLuint textureID;

public:
  Floor(HeightMap heightMap)
  {
    this->points = heightMap.getPoints();
    this->gridWidth = static_cast<int>(sqrt(points.size()));
    this->gridHeight = gridWidth;
    computeNormals();
  }

  void loadTexture()
  {
    Bmp bmp(fileName.c_str());
    bmp.convertBGRtoRGB();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp.getWidth(), bmp.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.getImage());
  }

  Vector3 crossProduct(const Vector3 &v1, const Vector3 &v2)
  {
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x);
  }

  Vector3 computeTriangleNormal(Vector3 &p1, Vector3 &p2, Vector3 &p3)
  {
    Vector3 edge1 = p2 - p1;
    Vector3 edge2 = p3 - p1;
    Vector3 normal = crossProduct(edge1, edge2);
    normal.normalize();
    return normal;
  }

  void computeNormals()
  {
    normals.resize(points.size(), Vector3(0, 0, 0));
    for (int z = 0; z < gridHeight - 1; z++)
    {
      for (int x = 0; x < gridWidth - 1; x++)
      {
        Vector3 p1 = points[z * gridWidth + x];
        Vector3 p2 = points[z * gridWidth + (x + 1)];
        Vector3 p3 = points[(z + 1) * gridWidth + x];
        Vector3 normal1 = computeTriangleNormal(p1, p2, p3);
        normals[z * gridWidth + x] += normal1;
        normals[z * gridWidth + (x + 1)] += normal1;
        normals[(z + 1) * gridWidth + x] += normal1;
        Vector3 p4 = points[(z + 1) * gridWidth + (x + 1)];
        Vector3 normal2 = computeTriangleNormal(p2, p4, p3);
        normals[z * gridWidth + (x + 1)] += normal2;
        normals[(z + 1) * gridWidth + (x + 1)] += normal2;
        normals[(z + 1) * gridWidth + x] += normal2;
      }
    }
    for (auto &normal : normals)
    {
      normal.normalize();
    }
  }

  void render()
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int z = 0; z < gridHeight - 1; z++)
    {
      glBegin(GL_TRIANGLE_STRIP);
      for (int x = 0; x < gridWidth; x++)
      {
        int index1 = z * gridWidth + x;
        int index2 = (z + 1) * gridWidth + x;
        Vector3 p1 = points[z * gridWidth + x];
        Vector3 p2 = points[(z + 1) * gridWidth + x];

        glTexCoord2f((float)x / (gridWidth - 1), (float)z / (gridHeight - 1));
        glNormal3f(normals[index1].x, normals[index1].y, normals[index1].z);
        glVertex3f(p1.x, p1.y, p1.z);

        glTexCoord2f((float)x / (gridWidth - 1), (float)(z + 1) / (gridHeight - 1));
        glNormal3f(normals[index2].x, normals[index2].y, normals[index2].z);
        glVertex3f(p2.x, p2.y, p2.z);
      }
      glEnd();
    }
    glDisable(GL_TEXTURE_2D);
  }
};
