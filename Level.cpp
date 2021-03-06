#include "Level.h"


Level::Level(const LevelConfig &level_config)
    : 
    _screen_buffer(window_width, window_height),
    _background_buffer(window_width, window_height),
    _opening(level_config.opening_path),
    _level_map(level_config.map_path),
		_player(_level_map.PlayerCoords()),
    _exit(_level_map.ExitCoords())
{
  DrawBackground();
}


void Level::ShowOpening(GLFWwindow *window)
{
  _opening.Draw(_screen_buffer);
  Fade(window, _screen_buffer, FadeDirection::IN);
  Fade(window, _screen_buffer, FadeDirection::OUT);
}

LevelResult Level::Run(GLFWwindow *window, InputState &input)
{
  _background_buffer.Draw(_screen_buffer);
  Fade(window, _screen_buffer, FadeDirection::IN);

  _player.Draw(_screen_buffer, _background_buffer);
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    MapElement touched_by_player{ MapElement::FLOOR };
    ProcessKeyPressing(input, touched_by_player);

    switch (touched_by_player) {
      case MapElement::EMPTY: {
        _reach_the_exit = false;
        _player.Draw(_screen_buffer, _background_buffer);
        Fade(window, _screen_buffer, FadeDirection::OUT);
        return LevelResult::DIED;
      } case MapElement::FAKE_WALL: {
        _reach_the_exit = false;
        const Tile &floor_tile = map_tiles.at(MapElement::FLOOR);
        floor_tile.DrawBackground(_background_buffer, _player.GetCoords());
        _player.Draw(_screen_buffer, _background_buffer);
      } case MapElement::FLOOR: {
        _reach_the_exit = false;
        _player.Draw(_screen_buffer, _background_buffer);
        break;
      } case MapElement::EXIT: {
        if (_reach_the_exit) {
          if (_exit.IsOpen()) {
            _player.Draw(_screen_buffer, _background_buffer);
            Fade(window, _screen_buffer, FadeDirection::OUT);
            return LevelResult::WON;
          }
        } else {
          _reach_the_exit = true;
        }
        _player.Draw(_screen_buffer, _background_buffer);
      } default: {
        break;
      }
    }

    DisplayScreenBuffer(window, _screen_buffer);
  }

  return LevelResult::EXIT;
}

void Level::ShowEnding(GLFWwindow *window, LevelResult result)
{
  switch (result) {
    case LevelResult::DIED:
      [[fallthrough]];
    case LevelResult::WON: {
      Image ending = _endings.at(result);
      Fade(window, ending, FadeDirection::IN);
      Fade(window, ending, FadeDirection::OUT);
    }
      [[fallthrough]];
    case LevelResult::EXIT:
      glfwTerminate();
  }
}

void Level::DisplayScreenBuffer(GLFWwindow *window, const Image &screen_buffer)
{
  glDrawPixels(window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, screen_buffer.Data()); GL_CHECK_ERRORS;
  glfwSwapBuffers(window);
}

void Level::Fade(GLFWwindow *window, const Image &orig_img, FadeDirection dir)
{
  for (int i = 0; i < fade_iterations; ++i) {
    double dimming_factor;

    if (dir == FadeDirection::OUT) {
      dimming_factor = static_cast<double>(fade_iterations - i - 1) / fade_iterations;
    } else if (dir == FadeDirection::IN) {
      dimming_factor = static_cast<double>(i) / fade_iterations;
    }

    Image dimmed_scrren_buffer{ orig_img * dimming_factor };

    DisplayScreenBuffer(window, dimmed_scrren_buffer);
  }
}


void Level::DrawBackground()
{
  const Tile &floor_tile = map_tiles.at(MapElement::FLOOR);
  
  for (int y = 0; y < LevelMap::tiles_y; ++y) {
    for (int x = 0; x < LevelMap::tiles_x; ++x) {
      Coords map_coords{ x, y };
      Coords img_coords{ x * Tile::tile_size, y * Tile::tile_size };

      MapElement map_element = _level_map.GetMapElement(map_coords);
      const Tile &tile = map_tiles.at(map_element);

      floor_tile.DrawBackground(_background_buffer, img_coords);
      tile.DrawOverBackground(_background_buffer, img_coords, _background_buffer);
    }
  }
  _exit.Draw(_background_buffer, _background_buffer);
}

void Level::ProcessKeyPressing(InputState &input, MapElement &touched)
{
  if (input.keys[GLFW_KEY_W]) {
    _player.ProcessInput(MovementDir::UP, _level_map, touched);
  } else if (input.keys[GLFW_KEY_S]) {
    _player.ProcessInput(MovementDir::DOWN, _level_map, touched);
  } else if (input.keys[GLFW_KEY_A]) {
    _player.ProcessInput(MovementDir::LEFT, _level_map, touched);
  } else if (input.keys[GLFW_KEY_D]) {
    _player.ProcessInput(MovementDir::RIGHT, _level_map, touched);
  } else if (input.keys[GLFW_KEY_E]) {
    if (_reach_the_exit) {
      OpenTheExit();
      touched = MapElement::EXIT;
    } else {
      touched = MapElement::FLOOR;
    }
  } else {
    if (_reach_the_exit) {
      touched = MapElement::EXIT;
    } else {
      touched = MapElement::FLOOR;
    }
  }
}

void Level::OpenTheExit()
{ 
  const Tile &floor_tile = map_tiles.at(MapElement::FLOOR);
  floor_tile.DrawBackground(_background_buffer, _level_map.ExitCoords());

  _exit.Open();
  _exit.Draw(_background_buffer, _background_buffer);

  _background_buffer.Draw(_screen_buffer);
}


const std::map<LevelResult, const Image> Level::_endings{
	{ LevelResult::DIED, Image("resources/game_endings/died.png") },
	{ LevelResult::WON, Image("resources/game_endings/won.png") }
};
