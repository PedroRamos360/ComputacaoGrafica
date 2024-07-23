#include "./Vector3.h"
#include <vector>

using namespace std;

class HeightMap
{
private:
  vector<Vector3> points;

  void generateHeightMap()
  {
    int maxX = 100;
    int maxZ = 100;
    for (int x = 0; x < maxX; ++x)
    {
      for (int z = 0; z < maxZ; ++z)
      {
        float y = sinf(x * 0.1f) * cosf(z * 0.1f) * 10.0f;
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