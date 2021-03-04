#include "Image.h"


Image::Image(const std::string &path)
{   
  ImageLoader img(path);

  if (img.Data() != nullptr) {
    _width = img.Width();
    _height = img.Height();
    _data = new Pixel[_height * _width];

    for (int y = 0; y < _height; ++y) {
      for (int x = 0; x < _width; ++x) {
        _data[y * _width + x] = img.Data()[y * _width + x];
      }
    }
  }
}

Image::Image(int width, int height)
{
  _data = new Pixel[width * height]{};

  if(_data != nullptr)
  {
    _width = width;
    _height = height;
  }
}

Image::Image(Image &&rhs)
    : _width(rhs._width),
    _height(rhs._height),
    _data(rhs._data)
{
  rhs._data = nullptr;
}

Image::Image(const Image &rhs)
    :  _width(rhs._width),
    _height(rhs._height),
    _data(new Pixel[rhs._height * rhs._width])
{
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      _data[y * _width + x] = rhs._data[y * _width + x];
    }
  }
}

Image::~Image()
{
  if (_data != nullptr) {
    delete[] _data;
  }
}

const Pixel &Image::GetPixel(const Coords &coords) const
{
  return _data[_width * coords.Y() + coords.X()];
}

void Image::PutPixel(const Coords &coords, const Pixel &pix)
{
  _data[_width * coords.Y() + coords.X()] = pix;
}


Pixel *Image::Data()
{
	return _data;
}