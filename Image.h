#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>

constexpr int TILE_SIZE = 24;

struct Coords
{
  int x{ 0 };
  int y{ 0 };
};

struct Pixel
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

constexpr Pixel backgroundColor{255, 0, 0, 0};

class Image
{
public:
  explicit Image(const std::string &path);
  Image(int width, int height, int channels = 4);

  Pixel* Data()
  {
    return _data;
  }

  Pixel GetPixel(const Coords &coords) const
  {
    return _data[_width * coords.y + coords.x];
  }
  void PutPixel(const Coords &coords, const Pixel &pix)
  {
    _data[_width * coords.y + coords.x] = pix;
  }

  ~Image();

private:
  int _width{ -1 };
  int _height{ -1 };
  int _channels{ 3 };
  size_t _size{ 0 };
  Pixel *_data{ nullptr };
  bool _self_allocated{ false };
};



#endif //MAIN_IMAGE_H
