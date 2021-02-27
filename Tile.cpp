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

const Pixel &Tile::GetPixel(const Coords &coords) const
{
  return _data[(tile_size - coords.y - 1) * tile_size + coords.x];  // tile is inverted along the y axis
}

void Tile::DrawOverBackground(Image &screen, const Coords &coords, const Image &background) const
{
  for (int y = 0; y < tile_size; ++y) {
    for (int x = 0; x < tile_size; ++x) {
      Coords tile_coords{ x, y };
      Coords screen_coords{ coords.x + x, coords.y + y };
      Pixel bg_pix = background.GetPixel(screen_coords);
      Pixel pix = GetPixel(tile_coords);

      double alpha = pix.a / 255.0;

      Pixel blendend_pix{
        .r = static_cast<uint8_t>(pix.r * alpha + bg_pix.r * (1 - alpha)),
        .g = static_cast<uint8_t>(pix.g * alpha + bg_pix.g * (1 - alpha)),
        .b = static_cast<uint8_t>(pix.b * alpha + bg_pix.b * (1 - alpha)),
        .a = static_cast<uint8_t>(pix.a * alpha + bg_pix.a * (1 - alpha))
      };

      screen.PutPixel(screen_coords, blendend_pix);
    }
  }
}