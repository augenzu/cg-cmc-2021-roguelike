#ifndef MAIN_IMAGE_LOADER_H
#define MAIN_IMAGE_LOADER_H

#include "Coords.h"

#include <iostream>
#include <string>


struct Pixel
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};


class ImageLoader
{
public:
  explicit ImageLoader(const std::string &path);

  Pixel* Data() { return _data; }
  int Width() const { return _width; }
  int Height() const { return _height; }

  ~ImageLoader();

private:
  int _width{ -1 };
  int _height{ -1 };
  int _channels{ 4 };
  size_t _size{ 0 };
  Pixel *_data{ nullptr };
  bool _self_allocated{ false };
};


#endif // MAIN_IMAGE_LOADER_H
