#include "LevelMap.h"


LevelMap::LevelMap()
{
  for (int y = 0; y < tiles_y; ++y) {
    std::vector<MapElement> row{ static_cast<size_t>(tiles_x), MapElement::EMPTY };
    _data.push_back(row);
  }
}

void LevelMap::Read(const std::string &path)
{
  std::ifstream fin{ path };

  for (int y = 0; y < tiles_y; ++y) {
    std::string row;
    std::getline(fin, row);

    for (int x = 0; x < tiles_x; ++x) {
      _data[y][x] = map_elements.at(row[x]);
      if (_data[y][x] == MapElement::PLAYER) {
        _player_coords = { x, tiles_y - y - 1 };
        _data[y][x] = MapElement::FLOOR;           // obviously under a player is a floor
      }
    }
  }
}

MapElement LevelMap::GetMapElement(const Coords &coords) const
{
  return _data[tiles_y - coords.Y() - 1][coords.X()];  // level map is inverted along the y axis
}