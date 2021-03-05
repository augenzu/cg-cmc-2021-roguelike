#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

// #include "Image.h"

// #include <vector>
// #include <string>


// class LevelComponents
// {
// public:
//   LevelComponents(const std::string &opening_path, const std::string &map_path)
//       : _opening(opening_path), _map_path(map_path) {}
//   LevelComponents(const LevelComponents &rhs)
//       : _opening(rhs._opening), _map_path(rhs._map_path) {}
  
//   ~LevelComponents() = default;

//   const Image &Opening() const { return _opening; }
//   const std::string &MapPath() const { return _map_path; }

// private:
//   const Image _opening;
//   const std::string _map_path;
// };


// const std::vector<LevelComponents> levels{
//   { "resources/level_openings/level_0.png", "resources/level_maps/level_0.txt" },
//   { "resources/level_openings/level_1.png", "resources/level_maps/level_1.txt" },
//   { "resources/level_openings/level_2.png", "resources/level_maps/level_2.txt" }
// };










#include "common.h"
#include "Coords.h"
#include "Image.h"
#include "InputState.h"
#include "LevelMap.h"
#include "MapElements.h"
#include "Player.h"
#include "Tile.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <vector>


struct LevelConfig
{
  const std::string opening_path;
  const std::string map_path;
};

const std::vector<LevelConfig> level_configs{
  { "resources/level_openings/level_0.png", "resources/level_maps/level_0.txt" },
  { "resources/level_openings/level_1.png", "resources/level_maps/level_1.txt" },
  { "resources/level_openings/level_2.png", "resources/level_maps/level_2.txt" }
};


enum class LevelResult
{
  LOST,
  WON,
  EXIT
};


class Level
{
public:
  static constexpr int window_width{ LevelMap::tiles_x * Tile::tile_size };
  static constexpr int window_height{ LevelMap::tiles_y * Tile::tile_size };

  explicit Level(const LevelConfig &level_config);
  Level(const Level &) = delete;
  Level(Level &&) = delete;
  ~Level() = default;

  void ShowOpening(GLFWwindow *window);
  LevelResult Run(GLFWwindow *window, InputState &input);
  static void ShowEnding(GLFWwindow *window, LevelResult result);

private:
  enum class FadeDirection
  {
    IN,
    OUT
  };
  static void Fade(GLFWwindow *window, const Image &orig_img, FadeDirection dir = FadeDirection::OUT);
  static constexpr int fade_iterations{ 50 };

  void DrawBackground();
  void ProcessPlayerMovement(InputState &input, MapElement &touched);

  Image _screen_buffer{ window_width, window_height };
  Image _background_buffer{ window_width, window_height };
  Image _opening;
  static const std::map<LevelResult, const Image> _endings;
  LevelMap _level_map;
  Player _player;
};


#endif // MAIN_LEVEL_H