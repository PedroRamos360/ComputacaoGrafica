#include <vector>
#include <cstdlib>
#include <ctime>
#include "Tree.h"
using namespace std;

class TreeGenerator
{
private:
  vector<Tree> trees;

  void generateTrees()
  {
    int maxX = 20;
    int maxZ = 20;
    srand(static_cast<unsigned int>(time(0)));
    const int numTrees = 30;
    for (int i = 0; i < numTrees; ++i)
    {
      float x = static_cast<float>(rand() % (maxX * 2) - maxX);
      float z = static_cast<float>(rand() % (maxZ * 2) - maxZ);
      trees.push_back(Tree(Vector3(x, 0, z)));
    }
  }

public:
  TreeGenerator()
  {
    generateTrees();
  }

  void renderTrees()
  {
    for (Tree &tree : trees)
    {
      tree.render();
    }
  }
};
