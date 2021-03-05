#include "Level.h"


Level::Level(const LevelConfig &level_config)
    : 
    _screen_buffer(window_width, window_height),
    _background_buffer(window_width, window_height),
    _opening(level_config.opening_path),
    _level_map(level_config.map_path),
		_player(_level_map.PlayerCoords() * Tile::tile_size)
{
  DrawBackground();
}


void Level::ShowOpening(GLFWwindow *window)
{
  for (int i = 0; i < 50; ++i) {
    _opening.Draw(_screen_buffer);

    glDrawPixels(window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, _screen_buffer.Data()); GL_CHECK_ERRORS;
    glfwSwapBuffers(window);
  }	
}

LevelResult Level::Run(GLFWwindow *window, InputState &input)
{
  _background_buffer.Draw(_screen_buffer);
  _player.Draw(_screen_buffer, _background_buffer);
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    MapElement touched_by_player{ MapElement::FLOOR };
    ProcessPlayerMovement(input, touched_by_player);

    switch (touched_by_player) {
      case MapElement::EMPTY: {
        _player.Draw(_screen_buffer, _background_buffer);
        return LevelResult::LOST;
      } case MapElement::FAKE_WALL: {
        const Tile &floor_tile = tiles.at(MapElement::FLOOR);
        floor_tile.DrawBackground(_background_buffer, _player.GetCoords());
        _player.Draw(_screen_buffer, _background_buffer);
      } case MapElement::FLOOR: {
        _player.Draw(_screen_buffer, _background_buffer);
        break;
      } case MapElement::EXIT: {
        const Tile &floor_tile = tiles.at(MapElement::FLOOR);
        floor_tile.DrawBackground(_background_buffer, _player.GetCoords());
        _player.Draw(_screen_buffer, _background_buffer);
        return LevelResult::WON;
      } default: {
        break;
      }
    }

    glDrawPixels(window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, _screen_buffer.Data()); GL_CHECK_ERRORS;
    glfwSwapBuffers(window);
  }

  return LevelResult::EXIT;
}

void Level::ShowEnding(GLFWwindow *window, LevelResult result)
{
  switch (result) {
    case LevelResult::LOST:
      [[fallthrough]];
    case LevelResult::WON: {
      Image ending = _endings.at(result);
      for (int i = 0; i < 50; ++i) {
        glDrawPixels(window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, ending.Data()); GL_CHECK_ERRORS;
        glfwSwapBuffers(window);
      }
    }
      [[fallthrough]];
    case LevelResult::EXIT:
      glfwTerminate();
  }
}


void Level::DrawBackground()
{
  const Tile &floor_tile = tiles.at(MapElement::FLOOR);
  
  for (int y = 0; y < LevelMap::tiles_y; ++y) {
    for (int x = 0; x < LevelMap::tiles_x; ++x) {
      Coords map_coords{ x, y };
      Coords img_coords{ x * Tile::tile_size, y * Tile::tile_size };

      MapElement map_element = _level_map.GetMapElement(map_coords);
      const Tile &tile = tiles.at(map_element);

      floor_tile.DrawBackground(_background_buffer, img_coords);
      tile.DrawOverBackground(_background_buffer, img_coords, _background_buffer);
    }
  }
}

void Level::ProcessPlayerMovement(InputState &input, MapElement &touched)
{
  if (input.keys[GLFW_KEY_W]) {
    _player.ProcessInput(MovementDir::UP, _level_map, touched);
  } else if (input.keys[GLFW_KEY_S]) {
    _player.ProcessInput(MovementDir::DOWN, _level_map, touched);
  } else if (input.keys[GLFW_KEY_A]) {
    _player.ProcessInput(MovementDir::LEFT, _level_map, touched);
  } else if (input.keys[GLFW_KEY_D]) {
    _player.ProcessInput(MovementDir::RIGHT, _level_map, touched);
  } else {
    touched = MapElement::FLOOR;
  }
}


const std::map<LevelResult, const Image> Level::_endings{
	{ LevelResult::LOST, Image("resources/game_endings/lost.png") },
	{ LevelResult::WON, Image("resources/game_endings/won.png") }
};
