#include <GL/glut.h>
#include <chrono>

using namespace std;

class KeyboardManager
{
private:
  bool keyStates[256];
  bool specialKeyStates[256];
  bool wireframe = false;
  chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long long, std::nano>> lastTime = chrono::high_resolution_clock::now();

  float getDeltaTime()
  {
    chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long long, std::nano>> currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime.count();
  }

  static KeyboardManager *instance;
  Camera *camera;

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
    printf("Controles do teclado:\n");
    printf("W: Mover para frente\n");
    printf("S: Mover para tras\n");
    printf("A: Mover para a esquerda\n");
    printf("D: Mover para a direita\n");
    printf("Q: Mover para baixo\n");
    printf("E: Mover para cima\n");
    printf("Setas: Rotacionar a camera\n");
    printf("K: Alternar entre modo wireframe e solido\n");
  }

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
    keyStates[tolower(key)] = false;
  }

  void keyboardDown(unsigned char key, int x, int y)
  {
    keyStates[tolower(key)] = true;
    if (tolower(key) == 'k')
    {
      if (wireframe)
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframe = false;
      }
      else
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe = true;
      }
    }
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
    float deltaTime = getDeltaTime();
    float movementSpeed = 30 * deltaTime;
    float verticalRotationSpeed = 2 * deltaTime;
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
    if (keyStates['e'])
    {
      camera->translate(movementSpeed, UP);
    }
    if (keyStates['q'])
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
