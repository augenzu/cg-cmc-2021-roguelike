#include "Player.h"


void Player::ProcessInput(MovementDir dir,
    const LevelMap &level_map,
    MapElement &touched_by_player)
{
  int move_dist = _move_speed * 1;
  
  _dir = dir;
  _old_coords = _coords;

  Coords delta;

  if (dir == MovementDir::UP) {
    delta = { 0, move_dist };
  } else if (dir == MovementDir::DOWN) {
    delta = { 0, -move_dist };
  } else if (dir == MovementDir::RIGHT) {
    delta = { move_dist, 0 };
  } else if (dir == MovementDir::LEFT) {
    delta = { -move_dist, 0 };
  }

  _coords += delta;

  int tile_size = Tile::tile_size;

  std::pair<MapElement, MapElement> touched;

  if (dir == MovementDir::UP) {
    int map_y_up = (_coords.Y() + tile_size - 1) / tile_size;
    int map_x_left = _coords.X() / tile_size;
    int map_x_right = (_coords.X() + tile_size - 1) / tile_size;
    Coords map_coords_left{ map_x_left, map_y_up };
    Coords map_coords_right{ map_x_right, map_y_up };
    touched = std::make_pair(
        level_map.GetMapElement(map_coords_left),
        level_map.GetMapElement(map_coords_right)
    );
  } else if (dir == MovementDir::DOWN) {
    int map_y_down = _coords.Y() / tile_size;
    int map_x_left = _coords.X() / tile_size;
    int map_x_right = (_coords.X() + tile_size - 1) / tile_size;
    Coords map_coords_left{ map_x_left, map_y_down };
    Coords map_coords_right{ map_x_right, map_y_down };
    touched = std::make_pair(
        level_map.GetMapElement(map_coords_left),
        level_map.GetMapElement(map_coords_right)
    );
  } else if (dir == MovementDir::RIGHT) {
    int map_x_right = (_coords.X() + tile_size - 1) / tile_size;
    int map_y_down = _coords.Y() / tile_size;
    int map_y_up = (_coords.Y() + tile_size - 1) / tile_size;
    Coords map_coords_down{ map_x_right, map_y_down };
    Coords map_coords_up{ map_x_right, map_y_up };
    touched = std::make_pair(
        level_map.GetMapElement(map_coords_down),
        level_map.GetMapElement(map_coords_up)
    );
  } else if (dir == MovementDir::LEFT) {
    int map_x_left = _coords.X() / tile_size;
    int map_y_down = _coords.Y() / tile_size;
    int map_y_up = (_coords.Y() + tile_size - 1) / tile_size;
    Coords map_coords_down{ map_x_left, map_y_down };
    Coords map_coords_up{ map_x_left, map_y_up };
    touched = std::make_pair(
        level_map.GetMapElement(map_coords_down),
        level_map.GetMapElement(map_coords_up)
    );
  }

  if (touched.first == MapElement::INVALID) {
    touched_by_player = touched.second;
  } else if (touched.second == MapElement::INVALID) {
    touched_by_player = touched.first;
  } else if (touched.first == MapElement::EXIT
      || touched.second == MapElement::EXIT) {
    touched_by_player = MapElement::EXIT;
  } else if (touched.first == MapElement::EMPTY
      || touched.second == MapElement::EMPTY) {
    touched_by_player = MapElement::EMPTY;
  } else if (touched.first == MapElement::WALL
      || touched.second == MapElement::WALL) {
    touched_by_player = MapElement::WALL;
  } else if (touched.first == MapElement::FAKE_WALL
      || touched.second == MapElement::FAKE_WALL) {
    touched_by_player = MapElement::FAKE_WALL;
  } else {
    touched_by_player = MapElement::FLOOR;
  }

  if (touched_by_player == MapElement::INVALID
      || touched_by_player == MapElement::WALL) {
    _coords = _old_coords;
  }
}

void Player::Draw(Image &screen, const Image &background) const
{ 
  UpdateBackground(screen, background);

  const Tile &frame{ _frame_storage.GetFrame(_dir) };
  frame.DrawOverBackground(screen, _coords, background);
}

void Player::UpdateBackground(Image &screen, const Image &background) const
{
  int tile_size = Tile::tile_size;
  
  for (int y = _old_coords.Y(); y < _old_coords.Y() + tile_size; ++y) {
    for (int x = _old_coords.X(); x < _old_coords.X() + tile_size; ++x) {
      Coords screen_coords{ x, y };
      screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
    }
  }
}
