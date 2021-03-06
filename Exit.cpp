#include "Exit.h"


void Exit::Open()
{
  _state = State::OPEN;
}

void Exit::Draw(Image &screen, const Image &background) const
{
	const Tile &tile{ _tiles.at(_state) };
	tile.DrawOverBackground(screen, _coords, background);
}

bool Exit::IsOpen() const
{
	return _state == State::OPEN;
}
