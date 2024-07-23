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
        float y = sinf(x * 0.1f) * cosf(z * 0.1f);
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
