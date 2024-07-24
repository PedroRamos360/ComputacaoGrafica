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

  void generateHeightMap()
  {
    for (int x = -halfMaxX; x < halfMaxX; ++x)
    {
      for (int z = -halfMaxZ; z < halfMaxZ; ++z)
      {
        float y = (sinf(x * 0.1) * cosf(z * 0.1)) + (sinf(x * 0.3) / 3 * cosf(z * 0.3) / 3);
        points.push_back(Vector3(x, y * 2, z));
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
