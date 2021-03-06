#ifndef MAIN_LEVEL_MAP_H
#define MAIN_LEVEL_MAP_H

#include "Coords.h"
#include "MapElements.h"
#include "Tile.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


constexpr int TILES_X = 60, TILES_Y = 30;


class LevelMap
{
public:
  LevelMap(const std::string &path);
  ~LevelMap() = default;

  static const int tiles_x{ TILES_X };
  static const int tiles_y{ TILES_Y };

  MapElement GetMapElement(const Coords &coords) const;
  Coords PlayerCoords() const { return _player_coords; }
  Coords ExitCoords() const { return _exit_coords; }

private:
  std::vector<std::vector<MapElement>> _data;
  Coords _player_coords;
  Coords _exit_coords;

  bool AreValid(const Coords &coords) const;
};


#endif // MAIN_LEVEL_MAP_H