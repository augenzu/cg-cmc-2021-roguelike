#include "Player.h"

#include "Coords.h"


void Player::ProcessInput(MovementDir dir,
    const LevelMap &level_map,
    MapElement &touched)
{ 
  int move_dist = _move_speed * 1;
  
  _old_coords = _coords;

  int tile_size = Tile::tile_size;
  
  int extend_up = tile_size * 0.7;
  int extend_down = tile_size * -0.1;
  int extend_right = tile_size * 0.5;
  int extend_left = tile_size * -0.1;

  Coords img_extended_coords{ _coords };

  Coords delta;
  Coords extended_delta;

  if (dir == MovementDir::UP) {
    delta = { 0, move_dist };
    extended_delta = { 0, move_dist + extend_up };
  } else if (dir == MovementDir::DOWN) {
    delta = { 0, -move_dist };
    extended_delta = { 0, -move_dist - extend_down };
  } else if (dir == MovementDir::RIGHT) {
    delta = { move_dist, 0 };
    extended_delta = { move_dist + extend_right, 0 };
  } else if (dir == MovementDir::LEFT) {
    delta = { -move_dist, 0 };
    extended_delta = { -move_dist - extend_left, 0 };
  }

  _coords += delta;
  img_extended_coords += extended_delta;

  Coords map_extended_coords{ img_extended_coords / tile_size };
  touched = level_map.GetMapElement(map_extended_coords);

  if (touched == MapElement::STRONG_WALL
      || touched == MapElement::FRAGILE_WALL) {
    _coords = _old_coords;
  }
}

void Player::Draw(Image &screen, const Image &background) const
{ 
  UpdateBackground(screen, background);
  _tile.DrawOverBackground(screen, _coords, background);
}


bool Player::Moved(MovementDir dir) const
{
  if(dir == MovementDir::UP && _old_coords.Y() < _coords.Y()) {
    return true;
  } else if (dir == MovementDir::DOWN && _old_coords.Y() > _coords.Y()) {
    return true;
  } else if (dir == MovementDir::RIGHT && _old_coords.X() < _coords.X()) {
    return true;
  } else if (dir == MovementDir::LEFT && _old_coords.X() > _coords.X()) {
    return true;
  } else {
    return false;
  }
}

void Player::UpdateBackground(Image &screen, const Image &background) const
{
  if (Moved(MovementDir::UP)) {
    for (int y = _old_coords.Y(); y < _coords.Y(); ++y) {
      for (int x = _coords.X(); x < _coords.X() + Tile::tile_size; ++x) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  } else if (Moved(MovementDir::DOWN)) {
    for (int y = _coords.Y() + Tile::tile_size; y < _old_coords.Y() + Tile::tile_size; ++y) {
      for (int x = _coords.X(); x < _coords.X() + Tile::tile_size; ++x) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  } else if (Moved(MovementDir::RIGHT)) {
    for (int x = _old_coords.X(); x < _coords.X(); ++x) {
      for (int y = _coords.Y(); y < _coords.Y() + Tile::tile_size; ++y) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  } else if (Moved(MovementDir::LEFT)) {
    for (int x = _coords.X() + Tile::tile_size; x < _old_coords.X() + Tile::tile_size; ++x) {
      for (int y = _coords.Y(); y < _coords.Y() + Tile::tile_size; ++y) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  }
}
