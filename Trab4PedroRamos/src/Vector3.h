#include <math.h>
#include <stdio.h>
#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

class Vector3
{
public:
  float x, y, z;

  Vector3()
  {
    x = y = z = 0;
  }

  Vector3(float _x, float _y, float _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }

  Vector3 operator+(Vector3 v)
  {
    return Vector3(x + v.x, y + v.y, z + v.z);
  }

  Vector3 operator-(Vector3 v)
  {
    return Vector3(x - v.x, y - v.y, z - v.z);
  }

  Vector3 operator*(Vector3 v)
  {
    return Vector3(x * v.x, y * v.y, z * v.z);
  }

  Vector3 operator*(float v)
  {
    return Vector3(x * v, y * v, z * v);
  }

  Vector3 crossProduct(const Vector3 &v) const
  {
    return Vector3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x);
  }

  float dotProduct(Vector3 v)
  {
    return x * v.x + y * v.y + z * v.z;
  }

  void set(float _x, float _y, float _z)
  {
    x = _x;
    y = _y;
    z = _z;
  }

  void normalize()
  {
    float norm = (float)sqrt(x * x + y * y + z * z);

    if (norm == 0.0)
    {
      printf("\n\nNormalize::Divisao por zero");
      x = 1;
      y = 1;
      z = 1;
      return;
    }
    x /= norm;
    y /= norm;
    z /= norm;
  }
};

#endif
