#include "Player.h"


bool Player::Moved() const
{
  if(_coords.x == _old_coords.x && _coords.y == _old_coords.y)
    return false;
  else
    return true;
}

void Player::ProcessInput(MovementDir dir)
{
  int move_dist = _move_speed * 1;
  switch(dir)
  {
    case MovementDir::UP:
      _old_coords.y = _coords.y;
      _coords.y += move_dist;
      break;
    case MovementDir::DOWN:
      _old_coords.y = _coords.y;
      _coords.y -= move_dist;
      break;
    case MovementDir::LEFT:
      _old_coords.x = _coords.x;
      _coords.x -= move_dist;
      break;
    case MovementDir::RIGHT:
      _old_coords.x = _coords.x;
      _coords.x += move_dist;
      break;
    default:
      break;
  }
}

void Player::Draw(Image &screen)
{
  if(Moved())
  {
    for(int y = _old_coords.y; y /*<=*/< _old_coords.y + TILE_SIZE; ++y)
    {
      for(int x = _old_coords.x; x /*<=*/< _old_coords.x + TILE_SIZE; ++x)
      {
        screen.PutPixel({ x, y }, backgroundColor);
      }
    }
    _old_coords = _coords;
  }

  for(int y = _coords.y; y /*<=*/< _coords.y + TILE_SIZE; ++y)
  {
    for(int x = _coords.x; x /*<=*/< _coords.x + TILE_SIZE; ++x)
    {
      screen.PutPixel({ x, y }, _color);
    }
  }
}