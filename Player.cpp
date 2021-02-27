#include "Player.h"


bool Player::Moved(MovementDir dir) const
{
  if(dir == MovementDir::UP && _old_coords.y < _coords.y) {
    return true;
  } else if (dir == MovementDir::DOWN && _old_coords.y > _coords.y) {
    return true;
  } else if (dir == MovementDir::RIGHT && _old_coords.x < _coords.x) {
    return true;
  } else if (dir == MovementDir::LEFT && _old_coords.x > _coords.x) {
    return true;
  } else {
    return false;
  }
}

void Player::ProcessInput(MovementDir dir)
{
  _old_coords = _coords;
  
  int move_dist = _move_speed * 1;
  switch(dir)
  {
    case MovementDir::UP:
      _coords.y += move_dist;
      break;
    case MovementDir::DOWN:
      _coords.y -= move_dist;
      break;
    case MovementDir::RIGHT:
      _coords.x += move_dist;
      break;
    case MovementDir::LEFT:
      _coords.x -= move_dist;
      break;
    default:
      break;
  }
}

void Player::UpdateBackground(Image &screen, const Image &background)
{
  if (Moved(MovementDir::UP)) {
    for (int y = _old_coords.y; y < _coords.y; ++y) {
      for (int x = _coords.x; x < _coords.x + Tile::tile_size; ++x) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  } else if (Moved(MovementDir::DOWN)) {
    for (int y = _coords.y + Tile::tile_size; y < _old_coords.y + Tile::tile_size; ++y) {
      for (int x = _coords.x; x < _coords.x + Tile::tile_size; ++x) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  } else if (Moved(MovementDir::RIGHT)) {
    for (int x = _old_coords.x; x < _coords.x; ++x) {
      for (int y = _coords.y; y < _coords.y + Tile::tile_size; ++y) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  } else if (Moved(MovementDir::LEFT)) {
    for (int x = _coords.x + Tile::tile_size; x < _old_coords.x + Tile::tile_size; ++x) {
      for (int y = _coords.y; y < _coords.y + Tile::tile_size; ++y) {
        Coords screen_coords{ x, y };
        screen.PutPixel(screen_coords, background.GetPixel(screen_coords));
      }
    }
  }
}

void Player::Draw(Image &screen, const Image &background)
{ 
  UpdateBackground(screen, background);
  _tile.DrawOverBackground(screen, _coords, background);
}