#include <iostream>
#include <array>

class Matrix3x3
{
public:
  std::array<std::array<double, 3>, 3> matrix;
  Matrix3x3()
  {
    for (auto &row : matrix)
    {
      row.fill(0.0);
    }
  }

  Matrix3x3(const std::array<std::array<double, 3>, 3> &mat) : matrix(mat) {}

  Matrix3x3 operator*(const Matrix3x3 &other) const
  {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        result.matrix[i][j] = 0.0;
        for (int k = 0; k < 3; ++k)
        {
          result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        }
      }
    }
    return result;
  }

  void display() const
  {
    for (const auto &row : matrix)
    {
      for (const auto &val : row)
      {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }
  }
};
