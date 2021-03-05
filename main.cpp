#include "common.h"
#include "Coords.h"
#include "Image.h"
#include "InputState.h"
#include "Level.h"
#include "LevelMap.h"
#include "MapElements.h"
#include "Player.h"
#include "Tile.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>


static InputState input;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
  case GLFW_KEY_1:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  case GLFW_KEY_2:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    break;
	default:
		if (action == GLFW_PRESS)
      input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      input.keys[key] = false;
	}
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    input.captureMouse = !input.captureMouse;
  }

  if (input.captureMouse) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    input.capturedMouseJustNow = true;
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (input.firstMouse) {
    input.lastX = float(xpos);
    input.lastY = float(ypos);
    input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - input.lastX;
  GLfloat yoffset = input.lastY - float(ypos);

  input.lastX = float(xpos);
  input.lastY = float(ypos);
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  std::cout << "Controls: "<< std::endl;
  std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
  std::cout << "W, A, S, D - movement  "<< std::endl;
  std::cout << "press ESC to exit" << std::endl;

	return 0;
}


int main(int argc, char **argv)
{
	if(!glfwInit()) {
    return -1;
  }

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  constexpr int window_width = Level::window_width;
  constexpr int window_height = Level::window_height;

  GLFWwindow *window = glfwCreateWindow(window_width, window_height, "task1 base project", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); 

	glfwSetKeyCallback        (window, OnKeyboardPressed);  
	glfwSetCursorPosCallback  (window, OnMouseMove); 
  glfwSetMouseButtonCallback(window, OnMouseButtonClicked);

	if(initGL() != 0) {
		return -1;
  }
	
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR){
		gl_error = glGetError();
  }

  glViewport(0, 0, window_width, window_height);  GL_CHECK_ERRORS;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;

  
  LevelResult game_result{ LevelResult::WON };
  
  // game loop
  for (const auto &level_config : level_configs) {
    Level level(level_config);

    level.ShowOpening(window);
    game_result = level.Run(window, input);

    if (game_result != LevelResult::WON) {
      break;
    }
  }

  Level::ShowEnding(window, game_result);

	return 0;
}
