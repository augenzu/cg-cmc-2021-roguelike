#ifndef MAIN_LEVEL_MAP_H
#define MAIN_LEVEL_MAP_H


#include "MapElements.h"

#include "Coords.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


constexpr int TILES_X = 60, TILES_Y = 30;


class LevelMap
{
public:
  LevelMap();
  ~LevelMap() = default;

  static const int tiles_x{ TILES_X };
  static const int tiles_y{ TILES_Y };

  void Read(const std::string &path);
  MapElement GetMapElement(const Coords &coords) const;
  Coords PlayerCoords() const { return _player_coords; }

private:
  std::vector<std::vector<MapElement>> _data;
  Coords _player_coords{ 0, 0 };
};


#endif // MAIN_LEVEL_MAP_H