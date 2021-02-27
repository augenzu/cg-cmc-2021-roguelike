#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Tile.h"

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Player
{
  explicit Player(Coords coords = {.x = 10, .y = 10}) :
                 _coords(coords), _old_coords(_coords) {};

  bool Moved(MovementDir dir) const;
  void ProcessInput(MovementDir dir);

  void UpdateBackground(Image &screen, const Image &background);
  void Draw(Image &screen, const Image &background);

private:
  Coords _coords {.x = 10, .y = 10};
  Coords _old_coords {.x = 10, .y = 10};
  Pixel _color {.r = 0, .g = 255, .b = 0, .a = 255};
  int _move_speed = 4;
  const Tile _tile{ "resources/tiles/player.png" };
};

#endif //MAIN_PLAYER_H
