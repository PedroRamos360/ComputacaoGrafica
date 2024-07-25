#include "./Vector3.h"
#include <vector>
#include <cmath>

using namespace std;

class HeightMap
{
private:
  vector<Vector3> points;
  int maxX = 200;
  int maxZ = 200;
  int halfMaxX = maxX / 2;
  int halfMaxZ = maxZ / 2;

  float bezier(float t, float p0, float p1, float p2)
  {
    return (1 - t) * (1 - t) * p0 + 2 * (1 - t) * t * p1 + t * t * p2;
  }

  void generateHeightMap()
  {
    float p0 = 0.0f;
    float p1 = 10.0f;
    float p2 = 0.0f;

    for (int x = -halfMaxX; x < halfMaxX; ++x)
    {
      for (int z = -halfMaxZ; z < halfMaxZ; ++z)
      {
        float tx = (float)(x + halfMaxX) / maxX;
        float tz = (float)(z + halfMaxZ) / maxZ;
        float y = bezier(tx, p0, p1, p2) * bezier(tz, p0, p1, p2);
        points.push_back(Vector3(x, y, z));
      }
    }
  }

public:
  HeightMap()
  {
    generateHeightMap();
  }

  vector<Vector3> &getPoints()
  {
    return points;
  }
};
