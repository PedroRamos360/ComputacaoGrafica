#include <vector>
#include <cstdlib>
#include <ctime>
#include "Tree.h"
#include "HeightMap.h"
using namespace std;

class TreeGenerator
{
private:
  vector<Tree> trees;

  void generateTrees(HeightMap heightMap)
  {
    srand(static_cast<unsigned int>(time(0)));
    const int numTrees = 60;
    vector<Vector3> points = heightMap.getPoints();
    for (int i = 0; i < numTrees; ++i)
    {
      int randomIndex = rand() % points.size();
      Vector3 randomPoint = points[randomIndex];
      int randResult = rand() % 3;
      TreeType treeType;
      if (randResult == 0)
        treeType = CUBE;
      else if (randResult == 1)
        treeType = PYRAMID;
      else
        treeType = TETRAHEDRON;
      trees.push_back(Tree(randomPoint, treeType));
    }
  }

public:
  TreeGenerator(HeightMap heightMap)
  {
    generateTrees(heightMap);
  }

  void renderTrees()
  {
    for (Tree &tree : trees)
    {
      tree.render();
    }
  }
};
