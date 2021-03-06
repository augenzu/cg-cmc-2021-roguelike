#ifndef MAIN_EXIT_H
#define MAIN_EXIT_H


#include "Coords.h"
#include "Image.h"
#include "Tile.h"

#include <map>


class Exit
{
public:
  explicit Exit(Coords coords)
      : _coords(coords) {}

	void Open();
	void Draw(Image &screen, const Image &background) const;
	
	bool IsOpen() const;

private:
	Coords _coords; 

  enum class State
  {
		CLOSE,
		OPEN
  };
	State _state{ State::CLOSE };
  const std::map<State, const Tile> _tiles{
		{ State::CLOSE, Tile("resources/tiles/map/exit/close.png") },
		{ State::OPEN, Tile("resources/tiles/map/exit/open.png") }
	};
};


#endif // MAIN_EXIT_H
