#ifndef MAIN_MAP_ELEMENTS_H
#define MAIN_MAP_ELEMENTS_H

#include "Tile.h"

#include <map>

enum class MapElement
{
  EMPTY,
  STRONG_WALL,
  FRAGILE_WALL,
  FAKE_WALL,
  FLOOR,
  PLAYER,
  EXIT
};

const std::map<char, const MapElement> map_elements{
  { ' ', MapElement::EMPTY },
  { '#', MapElement::STRONG_WALL },
  { '?', MapElement::FRAGILE_WALL },
  { '%', MapElement::FAKE_WALL },
  { '.', MapElement::FLOOR },
  { '@', MapElement::PLAYER },
  { 'x', MapElement::EXIT }
};

const std::map<MapElement, const Tile> tiles{
  { MapElement::EMPTY, Tile("resources/tiles/empty.png") },
  { MapElement::STRONG_WALL, Tile("resources/tiles/strong_wall.png") },
  { MapElement::FRAGILE_WALL, Tile("resources/tiles/fragile_wall.png") },
  { MapElement::FAKE_WALL, Tile("resources/tiles/fake_wall.png") },
  { MapElement::FLOOR, Tile("resources/tiles/floor.png") },
  { MapElement::PLAYER, Tile("resources/tiles/player.png") },
  { MapElement::EXIT, Tile("resources/tiles/exit.png") }
};

#endif // MAIN_MAP_ELEMENTS_H