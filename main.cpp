#include "common.h"
#include "Coords.h"
#include "Image.h"
#include "LevelMap.h"
#include "MapElements.h"
#include "Player.h"
#include "Tile.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>


const std::vector<std::string> level_map_text_files{
  "resources/level_maps/level_0.txt",
  "resources/level_maps/level_1.txt",
  "resources/level_maps/level_2.txt",
};


void DrawBackground(Image &screen,
    const LevelMap &level_map,
    const std::map<MapElement, const Tile> &tiles)
{
  const Tile &floor_tile = tiles.at(MapElement::FLOOR);
  
  for (int y = 0; y < LevelMap::tiles_y; ++y) {
    for (int x = 0; x < LevelMap::tiles_x; ++x) {
      Coords map_coords{ x, y };
      Coords img_coords{ x * TILE_SIZE, y * TILE_SIZE };

      MapElement map_element = level_map.GetMapElement(map_coords);
      const Tile &tile = tiles.at(map_element);

      floor_tile.DrawBackground(screen, img_coords);
      tile.DrawOverBackground(screen, img_coords, screen);
    }
  }
}


void EndTheGame()
{
  std::cout << "GAME OVER" << std::endl;
}


struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
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
      Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      Input.keys[key] = false;
	}
}

void processPlayerMovement(Player &player,
    const LevelMap &level_map,
    MapElement &touched)
{
  if (Input.keys[GLFW_KEY_W]) {
    player.ProcessInput(MovementDir::UP, level_map, touched);
  } else if (Input.keys[GLFW_KEY_S]) {
    player.ProcessInput(MovementDir::DOWN, level_map, touched);
  } else if (Input.keys[GLFW_KEY_A]) {
    player.ProcessInput(MovementDir::LEFT, level_map, touched);
  } else if (Input.keys[GLFW_KEY_D]) {
    player.ProcessInput(MovementDir::RIGHT, level_map, touched);
  } else {
    touched = MapElement::FLOOR;
  }
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    Input.captureMouse = !Input.captureMouse;

  if (Input.captureMouse)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Input.capturedMouseJustNow = true;
  }
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (Input.firstMouse)
  {
    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
    Input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - Input.lastX;
  GLfloat yoffset = Input.lastY - float(ypos);

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
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

  int window_width = LevelMap::tiles_x * Tile::tile_size;
  int window_height = LevelMap::tiles_y * Tile::tile_size;

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
	glfwSetScrollCallback     (window, OnMouseScroll);

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

  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  

  for (const auto &text_file : level_map_text_files) {
    LevelMap level_map{ text_file };
    
    Image backgroundBuffer(window_width, window_height);
    DrawBackground(backgroundBuffer, level_map, tiles);
    Image screenBuffer(window_width, window_height);
    DrawBackground(screenBuffer, level_map, tiles);

    Coords player_tile_coords{ level_map.PlayerCoords() };
    Coords player_img_coords{ player_tile_coords * Tile::tile_size };
    Player player{ player_img_coords };
    player.Draw(screenBuffer, backgroundBuffer);

    bool to_next_level{false};

    //game loop
    while (!to_next_level && !glfwWindowShouldClose(window))
    {
      GLfloat currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;
      glfwPollEvents();

      MapElement touched_by_player{ MapElement::FLOOR };
      processPlayerMovement(player, level_map, touched_by_player);

      switch (touched_by_player) {
        case MapElement::EMPTY: {
          player.Draw(screenBuffer, backgroundBuffer);
          glfwSetWindowShouldClose(window, GL_TRUE);
          break;
        }
        case MapElement::FAKE_WALL: {
          const Tile &floor_tile = tiles.at(MapElement::FLOOR);
          floor_tile.DrawBackground(backgroundBuffer, player.GetCoords());
          player.Draw(screenBuffer, backgroundBuffer);
          // [[fallthrough]];
        }
        case MapElement::FLOOR: {
          player.Draw(screenBuffer, backgroundBuffer);
          break;
        }
        case MapElement::EXIT: {
          const Tile &floor_tile = tiles.at(MapElement::FLOOR);
          floor_tile.DrawBackground(backgroundBuffer, player.GetCoords());
          player.Draw(screenBuffer, backgroundBuffer);
          to_next_level = true;
          break;
        }
        default: {
          break;
        }
      }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
      glDrawPixels (window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;

      glfwSwapBuffers(window);
    }

    if (glfwWindowShouldClose(window)) {
      break;
    }
  }

  EndTheGame();
	glfwTerminate();

	return 0;
}
