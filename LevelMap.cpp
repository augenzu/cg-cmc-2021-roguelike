#include "LevelMap.h"


LevelMap::LevelMap(const std::string &path)
{
  std::ifstream fin{ path };

  for (int y = 0; y < tiles_y; ++y) {
    std::vector<MapElement> map_row;

    std::string text_row;
    std::getline(fin, text_row);

    for (int x = 0; x < tiles_x; ++x) {
      MapElement map_element = map_elements.at(text_row[x]);
      if (map_element == MapElement::PLAYER) {
        map_element = MapElement::FLOOR;             // obviously under a player is a floor
        _player_coords = { x, tiles_y - y - 1 };     // determine player's coords
      }
      map_row.push_back(map_element);
    }

    _data.push_back(map_row);
  }
}

MapElement LevelMap::GetMapElement(const Coords &coords) const
{
  return _data[tiles_y - coords.Y() - 1][coords.X()];  // level map is inverted along the y axis
}