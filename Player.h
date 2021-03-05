#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Coords.h"
#include "Image.h"
#include "LevelMap.h"
#include "MapElements.h"
#include "Tile.h"

enum class MovementDir
{
  UP,
  DOWN,
  RIGHT,
  LEFT,
  NO_MOV
};

//-------------------------------------AnimationFrameStorage---------------------------------------------------//

#include <map>
#include <vector>


class AnimationFrameStorage
{
public:
  AnimationFrameStorage() = default;
  AnimationFrameStorage(const AnimationFrameStorage &) = delete;
  AnimationFrameStorage(AnimationFrameStorage &&) = delete;
  AnimationFrameStorage &operator=(const AnimationFrameStorage &) = delete;
  AnimationFrameStorage &operator=(AnimationFrameStorage &&) = delete;
  ~AnimationFrameStorage() = default;

  const Tile &GetFrame(MovementDir dir) const
  {
    int frame_number{ _counter.at(dir) / _animation_period };
    const Tile &frame{ _frames.at(dir)[frame_number] };
    ++_counter[dir];
    _counter[dir] %= (_frames_numbers.at(dir) * _animation_period);

    return frame;
  }

private:
  static constexpr int _animation_period{ 12 };

  const std::map<MovementDir, std::vector<Tile>> _frames{
    { MovementDir::UP, {
      Tile("resources/tiles/player/up/0.png"),
      Tile("resources/tiles/player/up/1.png"),
      Tile("resources/tiles/player/up/2.png"),
      Tile("resources/tiles/player/up/3.png")
    } },
    { MovementDir::DOWN, {
      Tile("resources/tiles/player/down/0.png"),
      Tile("resources/tiles/player/down/1.png"),
      Tile("resources/tiles/player/down/2.png"),
      Tile("resources/tiles/player/down/3.png")
    } },
    { MovementDir::RIGHT, {
      Tile("resources/tiles/player/right/0.png"),
      Tile("resources/tiles/player/right/1.png"),
      Tile("resources/tiles/player/right/2.png"),
      Tile("resources/tiles/player/right/3.png")
    } },
    { MovementDir::LEFT, {
      Tile("resources/tiles/player/left/0.png"),
      Tile("resources/tiles/player/left/1.png"),
      Tile("resources/tiles/player/left/2.png"),
      Tile("resources/tiles/player/left/3.png")
    } },
  };
  const std::map<MovementDir, int> _frames_numbers{
    { MovementDir::UP, _frames.at(MovementDir::UP).size() },
    { MovementDir::DOWN, _frames.at(MovementDir::DOWN).size() },
    { MovementDir::RIGHT, _frames.at(MovementDir::RIGHT).size() },
    { MovementDir::LEFT, _frames.at(MovementDir::LEFT).size() }
  };
  mutable std::map<MovementDir, int> _counter{
    { MovementDir::UP, 0 },
    { MovementDir::DOWN, 0 },
    { MovementDir::RIGHT, 0 },
    { MovementDir::LEFT, 0 }
  };
};


//-------------------------------------AnimationFrameStorage---------------------------------------------------//


class Player
{
public:
  explicit Player(Coords coords)
      : _coords(coords), _old_coords(_coords) {};

  Coords GetCoords() const { return _coords; }

  void ProcessInput(MovementDir dir, const LevelMap &level_map, MapElement &touched_by_player);
  void Draw(Image &screen, const Image &background) const;

private:
  void UpdateBackground(Image &screen, const Image &background) const;

  Coords _coords{ 10, 10 };
  Coords _old_coords{ 10, 10 };
  MovementDir _dir{ MovementDir::DOWN };

  Pixel _color {.r = 0, .g = 255, .b = 0, .a = 255};
  int _move_speed = 4;

  const AnimationFrameStorage _frame_storage;
};

#endif //MAIN_PLAYER_H
