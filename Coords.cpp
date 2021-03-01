#include "Coords.h"


Coords Coords::operator-() const
{
  return Coords(-_x, -_y);
}

Coords &Coords::operator+=(const Coords &rhs)
{
  _x += rhs._x;
  _y += rhs._y;
  return *this;
}

Coords &Coords::operator-=(const Coords &rhs)
{
  *this += -rhs;
  return *this;
}

Coords Coords::operator+(const Coords &rhs) const
{
  Coords res{ *this };
  res += rhs;
  return res;
}

Coords Coords::operator-(const Coords &rhs) const
{
  Coords res{ *this };
  res -= rhs;
  return res;
}

Coords &Coords::operator*=(int mul)
{
  _x *= mul;
  _y *= mul;
  return *this;
}

Coords &Coords::operator*=(double mul)
{
  _x *= mul;
  _y *= mul;
  return *this;
}

Coords &Coords::operator/=(int div)
{
  _x /= div;
  _y /= div;
  return *this;
}

Coords Coords::operator*(int mul) const
{
  Coords res{ *this };
  res *= mul;
  return res;  
}

Coords Coords::operator*(double mul) const
{
  Coords res{ *this };
  res *= mul;
  return res;  
}

Coords Coords::operator/(int div) const
{
  Coords res{ *this };
  res /= div;
  return res;  
}
