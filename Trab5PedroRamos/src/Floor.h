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
  int gridWidth;
  int gridHeight;
  GLuint textureID;

public:
  Floor(HeightMap heightMap)
  {
    this->points = heightMap.getPoints();
    this->gridWidth = static_cast<int>(sqrt(points.size()));
    this->gridHeight = gridWidth;
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

  void render()
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int z = 0; z < gridHeight - 1; ++z)
    {
      glBegin(GL_TRIANGLE_STRIP);
      for (int x = 0; x < gridWidth; ++x)
      {
        Vector3 p1 = points[z * gridWidth + x];
        Vector3 p2 = points[(z + 1) * gridWidth + x];

        glTexCoord2f((float)x / (gridWidth - 1), (float)z / (gridHeight - 1));
        glVertex3f(p1.x, p1.y, p1.z);

        glTexCoord2f((float)x / (gridWidth - 1), (float)(z + 1) / (gridHeight - 1));
        glVertex3f(p2.x, p2.y, p2.z);
      }
      glEnd();
    }
    glDisable(GL_TEXTURE_2D);
  }
};
