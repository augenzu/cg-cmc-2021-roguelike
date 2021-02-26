#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"

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

  bool Moved() const;
  void ProcessInput(MovementDir dir);
  void Draw(Image &screen);

private:
  Coords _coords {.x = 10, .y = 10};
  Coords _old_coords {.x = 10, .y = 10};
  Pixel _color {.r = 0, .g = 255, .b = 0, .a = 255};
  int _move_speed = 4;

};

#endif //MAIN_PLAYER_H
