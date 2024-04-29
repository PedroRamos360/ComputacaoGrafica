class ScoreBoard
{
private:
  int ballsCount = 0;

public:
  ScoreBoard(int *screenWidth, int *screenHeight)
  {
  }

  void render()
  {
    //  CV::translate()
  }

  int getBallsCount()
  {
    return this->ballsCount;
  }
}