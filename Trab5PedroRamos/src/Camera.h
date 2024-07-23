#include <math.h>

enum CameraDirection
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  FORWARD,
  BACKWARDS
};

class Camera
{
public:
  float eyex, eyey, eyez;
  float centerx, centery, centerz;

  Camera()
  {
    eyex = 0.0;
    eyey = 1.0;
    eyez = 10.0;
    centerx = 0.0;
    centery = 0.0;
    centerz = 0.0;
  }

  void rotate(float angle, CameraDirection cameraDirection)
  {
    float x = centerx - eyex;
    float z = centerz - eyez;
    float s = sin(angle);
    float c = cos(angle);

    switch (cameraDirection)
    {
    case LEFT:
      centerx = c * x + s * z + eyex;
      centerz = -s * x + c * z + eyez;
      break;
    case RIGHT:
      centerx = c * x - s * z + eyex;
      centerz = s * x + c * z + eyez;
      break;
    case UP:
      centery += angle;
      break;
    case DOWN:
      centery -= angle;
      break;
    }
  }
  void translate(float distance, CameraDirection cameraDirection)
  {
    float x = centerx - eyex;
    float z = centerz - eyez;
    float angle = atan2(z, x);
    float s = sin(angle);
    float c = cos(angle);

    switch (cameraDirection)
    {
    case FORWARD:
      eyex += distance * c;
      eyez += distance * s;
      centerx += distance * c;
      centerz += distance * s;
      break;
    case BACKWARDS:
      eyex -= distance * c;
      eyez -= distance * s;
      centerx -= distance * c;
      centerz -= distance * s;
      break;
    case LEFT:
      eyex += distance * s;
      eyez -= distance * c;
      centerx += distance * s;
      centerz -= distance * c;
      break;
    case RIGHT:
      eyex -= distance * s;
      eyez += distance * c;
      centerx -= distance * s;
      centerz += distance * c;
      break;
    case UP:
      eyey += distance;
      centery += distance;
      break;
    case DOWN:
      eyey -= distance;
      centery -= distance;
      break;
    }
  }
};