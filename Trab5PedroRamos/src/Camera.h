#include <cmath>
#include "Vector3.h"

enum CameraDirection
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  FORWARD,
  BACKWARDS
};

using namespace std;

class Camera
{
public:
  Vector3 eye;
  Vector3 center;
  Vector3 up;

  Camera()
      : eye(0.0f, 1.0f, 10.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f)
  {
    translate(150.0f, BACKWARDS);
  }

  void rotate(float angle, CameraDirection cameraDirection)
  {
    Vector3 direction = center - eye;
    direction.normalize();
    Vector3 right = direction.cross(up);
    right.normalize();

    switch (cameraDirection)
    {
    case LEFT:
      angle = -angle;

    case RIGHT:
    {
      direction = rotateAroundY(direction, angle);
      right = direction.cross(up);
      right.normalize();
      up = right.cross(direction);
      up.normalize();

      eye = center - direction;
      break;
    }

    case DOWN:
      angle = -angle;
    case UP:
    {
      direction = rotateAroundAxis(direction, right, angle);
      up = right.cross(direction);
      up.normalize();

      eye = center - direction;
      break;
    }
    }
  }

  void translate(float distance, CameraDirection cameraDirection)
  {
    Vector3 direction = center - eye;
    Vector3 right;
    direction.normalize();

    switch (cameraDirection)
    {
    case FORWARD:
      eye = eye + direction * distance;
      center = center + direction * distance;
      break;

    case BACKWARDS:
      eye = eye - direction * distance;
      center = center - direction * distance;
      break;

    case LEFT:
      right = direction.cross(Vector3(0.0f, 1.0f, 0.0f));
      right.normalize();
      eye = eye - right * distance;
      center = center - right * distance;
      break;

    case RIGHT:
      right = direction.cross(Vector3(0.0f, 1.0f, 0.0f));
      right.normalize();
      eye = eye + right * distance;
      center = center + right * distance;
      break;

    case UP:
      eye.y += distance;
      center.y += distance;
      break;

    case DOWN:
      eye.y -= distance;
      center.y -= distance;
      break;
    }
  }

private:
  Vector3 rotateAroundY(const Vector3 &vector, float angle)
  {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    Vector3 rotated;
    rotated.x = cosAngle * vector.x - sinAngle * vector.z;
    rotated.y = vector.y;
    rotated.z = sinAngle * vector.x + cosAngle * vector.z;

    return rotated;
  }

  Vector3 rotateAroundAxis(const Vector3 &vector, const Vector3 &axis, float angle)
  {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    Vector3 axisNorm = axis;
    axisNorm.normalize();

    Vector3 vectorValue = Vector3(vector.x, vector.y, vector.z);

    return vectorValue * cosAngle + (axisNorm.cross(vector)) * sinAngle + axisNorm * (axisNorm.dot(vector)) * (1.0f - cosAngle);
  }
};