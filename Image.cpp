#include "Image.h"


Image::Image(const std::string &path)
{   
  ImageLoader img(path);

  if (img) {
    _width = img.Width();
    _height = img.Height();
    _data = new Pixel[_height * _width];

    for (int y = 0; y < _height; ++y) {
      for (int x = 0; x < _width; ++x) {
         _data[y * _width + x] = img.GetPixel(x, y);
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

// for now only draws if 
// _height <= screen._height && _width <= screen._width
void Image::Draw(Image &screen) const
{
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      Coords img_coords{ x, y };
      Pixel pix = GetPixel(img_coords);

      screen.PutPixel(img_coords, pix);
    }
  }
}

Image &Image::operator*=(double mul)
{
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      Coords img_coords{ x, y };
      Pixel old_pix = GetPixel(img_coords);

      Pixel multed_pix{
        .r = static_cast<uint8_t>(old_pix.r * mul),
        .g = static_cast<uint8_t>(old_pix.g * mul),
        .b = static_cast<uint8_t>(old_pix.b * mul),
        .a = old_pix.a
      };

      PutPixel(img_coords, multed_pix);
    }
  }

  return *this;
}

Image Image::operator*(double mul) const
{
  Image multed_img{ *this };
  multed_img *= mul;

  return multed_img;
}

Pixel *Image::Data()
{
	return _data;
}
