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
    srand(static_cast<unsigned int>(time(0)));
    const int numTrees = 15;
    for (int i = 0; i < numTrees; ++i)
    {
      float x = static_cast<float>(rand() % 21 - 10);
      float z = static_cast<float>(rand() % 21 - 10);
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
