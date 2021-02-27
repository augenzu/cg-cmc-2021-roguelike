#include "Tile.h"

Tile::Tile(const std::string &path)
{   
  Image img(path);

  if (img.Data() != nullptr) {
    _data = new Pixel[tile_size * tile_size];

    for (int x = 0; x < tile_size; ++x) {
      for (int y = 0; y < tile_size; ++y) {
        _data[y * tile_size + x] = img.Data()[y * tile_size + x];
      }
    }
  }
}

Tile::Tile(Tile &&rhs)
    : _data(rhs._data)
{
  rhs._data = nullptr;
}

Tile::Tile(const Tile &rhs)
    : _data(new Pixel[tile_size * tile_size])
{
  for (int x = 0; x < tile_size; ++x) {
    for (int y = 0; y < tile_size; ++y) {
      _data[y * tile_size + x] = rhs._data[y * tile_size + x];
    }
  }
}

Tile::~Tile()
{
  if (_data != nullptr) {
    delete[] _data;
  }
}

const Pixel &Tile::GetPixel(int x, int y) const
{
  return _data[(tile_size - y - 1) * tile_size + x];  // tile is inverted along the y axis
}