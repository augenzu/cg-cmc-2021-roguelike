#ifndef MAIN_MAP_ELEMENTS_H
#define MAIN_MAP_ELEMENTS_H

#include "Tile.h"

#include <map>

enum class MapElement
{
  EMPTY,
  WALL,
  FAKE_WALL,
  FLOOR,
  PLAYER,
  EXIT,
  INVALID  // unexisting map element, is used to signal invalid coordinates
};

const std::map<char, const MapElement> map_elements{
  { ' ', MapElement::EMPTY },
  { '#', MapElement::WALL },
  { '%', MapElement::FAKE_WALL },
  { '.', MapElement::FLOOR },
  { '@', MapElement::PLAYER },
  { 'x', MapElement::EXIT }
};

const std::map<MapElement, const Tile> map_tiles{
  { MapElement::EMPTY, Tile("resources/tiles/map/empty.png") },
  { MapElement::WALL, Tile("resources/tiles/map/wall.png") },
  { MapElement::FAKE_WALL, Tile("resources/tiles/map/fake_wall.png") },
  { MapElement::FLOOR, Tile("resources/tiles/map/floor.png") },
  { MapElement::EXIT, Tile("resources/tiles/map/floor.png") }
};

#endif // MAIN_MAP_ELEMENTS_H