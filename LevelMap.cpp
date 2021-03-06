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
        _player_coords *= Tile::tile_size;
      } else if (map_element == MapElement::EXIT) {
        _exit_coords = { x, tiles_y - y - 1 };
        _exit_coords *= Tile::tile_size;
      }
      map_row.push_back(map_element);
    }

    _data.push_back(map_row);
  }
}

MapElement LevelMap::GetMapElement(const Coords &coords) const
{
  MapElement map_element;

  if (AreValid(coords)) {
    map_element = _data[tiles_y - coords.Y() - 1][coords.X()];  // level map is inverted along the y axis
  } else {
    map_element = MapElement::INVALID;
  }

  return map_element;
}

bool LevelMap::AreValid(const Coords &coords) const
{
  bool are_valid = (coords.X() >= 0 && coords.X() < tiles_x
      && coords.Y() >= 0 && coords.Y() < tiles_y);
  return are_valid;
}