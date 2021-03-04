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
  LEFT,
  RIGHT
};

class Player
{
public:
  explicit Player(Coords coords)
      : _coords(coords), _old_coords(_coords) {};

  Coords GetCoords() const { return _coords; }

  void ProcessInput(MovementDir dir, const LevelMap &level_map, MapElement &touched_by_player);
  void Draw(Image &screen, const Image &background) const;

private:
  bool Moved(MovementDir dir) const;
  void UpdateBackground(Image &screen, const Image &background) const;

  Coords _coords{ 10, 10 };
  Coords _old_coords{ 10, 10 };
  Pixel _color {.r = 0, .g = 255, .b = 0, .a = 255};
  int _move_speed = 4;
  const Tile _tile{ tiles.at(MapElement::PLAYER) };
};

#endif //MAIN_PLAYER_H
