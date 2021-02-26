#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>


Image::Image(const std::string &path)
{
  if((_data = (Pixel*) stbi_load(path.c_str(), &_width, &_height, &_channels, sizeof(Pixel))) != nullptr)
  {
    _size = _width * _height * _channels;
  }
}

Image::Image(int width, int height, int channels)
{
  _data = new Pixel[width * height]{};

  if(_data != nullptr)
  {
    _width = width;
    _height = height;
    _size = width * height * channels;
    _channels = channels;
    _self_allocated = true;
  }
}

Image::~Image()
{
  if(_self_allocated) {
    delete[] _data;
  }
  else {
    stbi_image_free(_data);
  }
}