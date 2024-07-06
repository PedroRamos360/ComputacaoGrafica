#include <math.h>
#include <stdio.h>
#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__
#include "Vector2.h"

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

  Vector3 translateZ(float d)
  {
    Vector3 r;
    r.x = x;
    r.y = y;
    r.z = z + d;
    return r;
  }

  Vector3 translateX(float d)
  {
    Vector3 r;
    r.x = x + d;
    r.y = y;
    r.z = z;
    return r;
  }

  Vector3 translateY(float d)
  {
    Vector3 r;
    r.x = x;
    r.y = y + d;
    r.z = z;
    return r;
  }

  Vector3 rotateY(float ang, Vector3 center = Vector3(0, 0, 0))
  {
    Vector3 r;
    x -= center.x;
    y -= center.y;
    z -= center.z;
    r.x = x * cos(ang) - z * sin(ang);
    r.y = y;
    r.z = x * sin(ang) + z * cos(ang);
    r.x += center.x;
    r.y += center.y;
    r.z += center.z;
    return r;
  }

  Vector3 rotateZ(float ang, Vector3 center = Vector3(0, 0, 0))
  {
    Vector3 r;
    x -= center.x;
    y -= center.y;
    z -= center.z;
    r.x = x * cos(ang) - y * sin(ang);
    r.y = x * sin(ang) + y * cos(ang);
    r.z = z;
    r.x += center.x;
    r.y += center.y;
    r.z += center.z;
    return r;
  }

  Vector3 rotateX(float ang, Vector3 center = Vector3(0, 0, 0))
  {
    Vector3 r;
    x -= center.x;
    y -= center.y;
    z -= center.z;
    r.x = x;
    r.y = y * cos(ang) - z * sin(ang);
    r.z = y * sin(ang) + z * cos(ang);
    r.x += center.x;
    r.y += center.y;
    r.z += center.z;
    return r;
  }

  Vector2 project(float d)
  {
    Vector2 r;
    r.x = x * d / z;
    r.y = y * d / z;
    return r;
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
