#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include "Image.h"

#include <vector>
#include <string>


class LevelComponents
{
public:
  LevelComponents(const std::string &opening_path, const std::string &map_path)
      : _opening(opening_path), _map_path(map_path) {}
  LevelComponents(const LevelComponents &rhs)
      : _opening(rhs._opening), _map_path(rhs._map_path) {}
  
  ~LevelComponents() = default;

  const Image &Opening() const { return _opening; }
  const std::string &MapPath() const { return _map_path; }

private:
  const Image _opening;
  const std::string _map_path;
};


const std::vector<LevelComponents> levels{
  { "resources/level_openings/level_0.png", "resources/level_maps/level_0.txt" },
  { "resources/level_openings/level_1.png", "resources/level_maps/level_1.txt" },
  { "resources/level_openings/level_2.png", "resources/level_maps/level_2.txt" }
};


#endif // MAIN_LEVEL_H