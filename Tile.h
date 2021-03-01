#ifndef MAIN_TILE_H
#define MAIN_TILE_H

#include "Coords.h"
#include "Image.h"

class Tile
{
public:
  static const int tile_size{ 24 };

  explicit Tile(const std::string &path);
  Tile(Tile &&rhs);
  Tile(const Tile &rhs);

  ~Tile();

  Tile &operator=(const Tile &rhs) = delete;
  Tile &operator=(Tile &&rhs) = delete;

  const Pixel &GetPixel(const Coords &coords) const;

  void DrawBackground(Image &screen, const Coords &coords) const;
  void DrawOverBackground(Image &screen, const Coords &coords, const Image &background) const;

private:
  Pixel *_data{ nullptr };
};

#endif //MAIN_TILE_H
