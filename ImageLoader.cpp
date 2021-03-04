#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


ImageLoader::ImageLoader(const std::string &path)
{
  if((_data = (Pixel*) stbi_load(path.c_str(), &_width, &_height, &_channels, sizeof(Pixel))) != nullptr)
  {
    _size = _width * _height * _channels;
  }
}

ImageLoader::~ImageLoader()
{
  if(_self_allocated) {
    delete[] _data;
  }
  else {
    stbi_image_free(_data);
  }
}