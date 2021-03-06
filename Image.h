#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H


#include "Coords.h"
#include "ImageLoader.h"

#include <iostream>


class Image
{
public:
  explicit Image(const std::string &path);
	Image(int width, int height);
  Image(Image &&rhs);
  Image(const Image &rhs);

  ~Image();

  Image &operator=(const Image &rhs) = delete;
  Image &operator=(Image &&rhs) = delete;

  const Pixel &GetPixel(const Coords &coords) const;
	void PutPixel(const Coords &coords, const Pixel &pix);

  void Draw(Image &screen) const;

  Image &operator*=(double mul);
  Image operator*(double mul) const;

	Pixel *Data() const;

private:
  int _width{ 0 };
  int _height{ 0 };
  Pixel *_data{ nullptr };
};


#endif // MAIN_IMAGE_H
