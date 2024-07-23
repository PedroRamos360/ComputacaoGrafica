#include <GL/glut.h>

class KeyboardManager
{
private:
  bool keyStates[256];
  bool specialKeyStates[256];

  static KeyboardManager *instance;
  Camera *camera;

  // Private constructor to prevent instantiation
  KeyboardManager(Camera *camera)
  {
    this->camera = camera;
    for (int i = 0; i < 256; ++i)
    {
      keyStates[i] = false;
      specialKeyStates[i] = false;
    }

    glutKeyboardUpFunc(keyboardUpWrapper);
    glutKeyboardFunc(keyboardDownWrapper);
    glutSpecialUpFunc(specialFuncUpWrapper);
    glutSpecialFunc(specialFuncDownWrapper);
  }

  // Static wrapper functions for GLUT callbacks
  static void keyboardUpWrapper(unsigned char key, int x, int y)
  {
    instance->keyboardUp(key, x, y);
  }

  static void keyboardDownWrapper(unsigned char key, int x, int y)
  {
    instance->keyboardDown(key, x, y);
  }

  static void specialFuncUpWrapper(int key, int x, int y)
  {
    instance->specialFuncUp(key, x, y);
  }

  static void specialFuncDownWrapper(int key, int x, int y)
  {
    instance->specialFuncDown(key, x, y);
  }

  void keyboardUp(unsigned char key, int x, int y)
  {
    keyStates[key] = false;
  }

  void keyboardDown(unsigned char key, int x, int y)
  {
    keyStates[key] = true;
  }

  void specialFuncUp(int key, int x, int y)
  {
    specialKeyStates[key] = false;
  }

  void specialFuncDown(int key, int x, int y)
  {
    specialKeyStates[key] = true;
  }

public:
  static KeyboardManager *getInstance(Camera *camera)
  {
    if (instance == nullptr)
    {
      instance = new KeyboardManager(camera);
    }
    return instance;
  }

  void processInput()
  {
    float movementSpeed = 0.5;
    float verticalRotationSpeed = 0.02;
    float horizontalRotationSpeed = verticalRotationSpeed;
    if (keyStates['w'])
    {
      camera->translate(movementSpeed, FORWARD);
    }
    if (keyStates['s'])
    {
      camera->translate(movementSpeed, BACKWARDS);
    }
    if (keyStates['a'])
    {
      camera->translate(movementSpeed, LEFT);
    }
    if (keyStates['d'])
    {
      camera->translate(movementSpeed, RIGHT);
    }
    if (keyStates['q'])
    {
      camera->translate(movementSpeed, UP);
    }
    if (keyStates['e'])
    {
      camera->translate(movementSpeed, DOWN);
    }
    if (specialKeyStates[GLUT_KEY_RIGHT])
    {
      camera->rotate(horizontalRotationSpeed, RIGHT);
    }
    if (specialKeyStates[GLUT_KEY_LEFT])
    {
      camera->rotate(horizontalRotationSpeed, LEFT);
    }
    if (specialKeyStates[GLUT_KEY_UP])
    {
      camera->rotate(verticalRotationSpeed, UP);
    }
    if (specialKeyStates[GLUT_KEY_DOWN])
    {
      camera->rotate(verticalRotationSpeed, DOWN);
    }
  }
};
