#include "common.h"
#include "Image.h"
#include "Player.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>


//-------------------------------------------MY-NEW-CODE------------------------------------------------------//

#include <fstream>
#include <iostream>
#include <map>
#include <vector>


constexpr int TILES_X = /*70*/10, TILES_Y = 6;

enum class MapElement
{
  EMPTY,
  WALL,
  FAKE_WALL,
  FLOOR,
  PLAYER,
  EXIT
};

std::map<char, const MapElement> map_elements{
  { ' ', MapElement::EMPTY },
  { '#', MapElement::WALL },
  { '%', MapElement::FAKE_WALL },
  { '.', MapElement::FLOOR },
  { 'x', MapElement::EXIT }
};

// const std::map<MapElement, const Image> tiles{
//   { MapElement::EMPTY, Image("resources/tiles/empty.png") },
//   { MapElement::WALL, Image("resources/tiles/wall.png") },
//   { MapElement::FAKE_WALL, Image("resources/fake_wall/empty.png") },
//   { MapElement::FLOOR, Image("resources/tiles/floor.png") },
//   { MapElement::EXIT, Image("resources/tiles/exit.png") }
// };


struct TileCoords
{
  int x, y;
};


class LevelMap
{
public:
  LevelMap(int tiles_x = TILES_X, int tiles_y = TILES_Y)
      : _tiles_x(tiles_x), _tiles_y(tiles_y)
  {
    for (int x = 0; x < _tiles_x; ++x) {
        std::vector<MapElement> row{ static_cast<size_t>(_tiles_y), MapElement::EMPTY };
        _data.push_back(row);
    }
  }
  ~LevelMap() = default;

  void Read(const std::string &path)
  {
    std::ifstream fin{ path };
    for (int x = 0; x < _tiles_x; ++x) {
      std::string row;
      fin >> row;
      std::cout << "row: " << row << std::endl;
      for (int y = 0; y < _tiles_y; ++y) {
        _data[x][y] = map_elements[row[y]];
      }
    }
  }

  int TilesX() const { return _tiles_x; }
  int TilesY() const { return _tiles_y; }
  MapElement GetMapElement(const TileCoords &coords) const
  {
    return _data[coords.x][coords.y];
  }

private:
  int _tiles_x{ TILES_X }, _tiles_y{ TILES_Y };
  std::vector<std::vector<MapElement>> _data;
};


void DrawBackgroundTile(Image &screen, const TileCoords &coords, const Image &tile)
{
  for (int x = 0; x < TILE_SIZE; ++x) {
    for (int y = 0; y < TILE_SIZE; ++y) {
      screen.PutPixel(coords.x * TILE_SIZE + x, coords.y * TILE_SIZE + y, tile.GetPixel(x, y));
    }
  }
}

void DrawBackground(Image &screen,
    const LevelMap &level_map,
    const std::map<MapElement, const Image> &tiles)
{
  for (int x = 0; x < level_map.TilesX(); ++x) {
    for (int y = 0; y < level_map.TilesY(); ++y) {
      TileCoords coords{ x, y };
      MapElement map_element = level_map.GetMapElement(coords);
      const Image &tile = tiles.at(map_element);
      DrawBackgroundTile(screen, coords, tile);
    }
  }
}


int main()
{
  // const std::map<MapElement, const Image> tiles{
  //   { MapElement::EMPTY, Image("resources/tiles/empty.png") },
  //   { MapElement::WALL, Image("resources/tiles/wall.png") },
  //   { MapElement::FAKE_WALL, Image("resources/fake_wall/empty.png") },
  //   { MapElement::FLOOR, Image("resources/tiles/floor.png") },
  //   { MapElement::EXIT, Image("resources/tiles/exit.png") }
  // };

  // std::cout << "EMPTY Image width: " << tiles.at(MapElement::EMPTY).Width() << std::endl;

  Image i("resources/tiles/empty.png");
  std::cout << "EMPTY Image width: " << i.Width() << std::endl;

  LevelMap level_map{};
  level_map.Read("resources/levels/level1.txt");
  
  return 0;
}


//-------------------------------------------MY-NEW-CODE------------------------------------------------------//


constexpr GLsizei WINDOW_WIDTH = TILES_X * TILE_SIZE, WINDOW_HEIGHT = TILES_Y * TILE_SIZE;

struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


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

void processPlayerMovement(Player &player)
{
  if (Input.keys[GLFW_KEY_W])
    player.ProcessInput(MovementDir::UP);
  else if (Input.keys[GLFW_KEY_S])
    player.ProcessInput(MovementDir::DOWN);
  if (Input.keys[GLFW_KEY_A])
    player.ProcessInput(MovementDir::LEFT);
  else if (Input.keys[GLFW_KEY_D])
    player.ProcessInput(MovementDir::RIGHT);
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
  // ...
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

// int main(int argc, char **argv)
// {
// 	if(!glfwInit())
//     return -1;

// //	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// //	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// //	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

//   GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
// 	if (window == nullptr)
// 	{
// 		std::cout << "Failed to create GLFW window" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}
	
// 	glfwMakeContextCurrent(window); 

// 	glfwSetKeyCallback        (window, OnKeyboardPressed);  
// 	glfwSetCursorPosCallback  (window, OnMouseMove); 
//   glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
// 	glfwSetScrollCallback     (window, OnMouseScroll);

// 	if(initGL() != 0) 
// 		return -1;
	
//   //Reset any OpenGL errors which could be present for some reason
// 	GLenum gl_error = glGetError();
// 	while (gl_error != GL_NO_ERROR)
// 		gl_error = glGetError();

// 	Point starting_pos{.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2};
// 	Player player{starting_pos};

// 	Image img("../resources/tex.png");
// 	Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);

//   glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
//   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;

//   //game loop
// 	while (!glfwWindowShouldClose(window))
// 	{
// 		GLfloat currentFrame = glfwGetTime();
// 		deltaTime = currentFrame - lastFrame;
// 		lastFrame = currentFrame;
//     glfwPollEvents();

//     processPlayerMovement(player);
//     player.Draw(screenBuffer);

// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
//     glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;

// 		glfwSwapBuffers(window);
// 	}

// 	glfwTerminate();
// 	return 0;
// }
