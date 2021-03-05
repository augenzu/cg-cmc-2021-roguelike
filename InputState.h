#ifndef MAIN_INPUT_STATE_H
#define MAIN_INPUT_STATE_H


#define GLFW_DLL
#include <GLFW/glfw3.h>


struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
};


#endif // MAIN_INPUT_STATE_H
