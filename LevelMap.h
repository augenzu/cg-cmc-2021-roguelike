#ifndef MAIN_LEVEL_MAP_H
#define MAIN_LEVEL_MAP_H


#include "MapElements.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


constexpr int TILES_X = 70, TILES_Y = 30;


class LevelMap
{
public:
  LevelMap(int tiles_x = TILES_X, int tiles_y = TILES_Y);
  ~LevelMap() = default;

  void Read(const std::string &path);

  int TilesX() const { return _tiles_x; }
  int TilesY() const { return _tiles_y; }

  MapElement GetMapElement(const Coords &coords) const;

  Coords PlayerCoords() const { return _player_coords; }

private:
  int _tiles_x{ TILES_X };
  int _tiles_y{ TILES_Y };
  std::vector<std::vector<MapElement>> _data;
  Coords _player_coords{ 0, 0 };
};


#endif // MAIN_LEVEL_MAP_H