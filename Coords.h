#ifndef MAIN_COORDS_H
#define MAIN_COORDS_H


class Coords
{
public:
  Coords(int x = 0, int y = 0) :_x(x), _y(y) {}
  Coords(const Coords &) = default;
  ~Coords() = default;
  Coords &operator=(const Coords &) = default;

  int X() const { return _x; }
  int Y() const { return _y; }

  Coords operator-() const;

  Coords &operator+=(const Coords &rhs);
  Coords &operator-=(const Coords &rhs);

  Coords operator+(const Coords &rhs) const;
  Coords operator-(const Coords &rhs) const;

  Coords &operator*=(int mul);
  Coords &operator*=(double mul);
  Coords &operator/=(int div);

  Coords operator*(int mul) const;
  Coords operator*(double mul) const;
  Coords operator/(int div) const;

private:
  int _x{ 0 };
  int _y{ 0 };
};


#endif //MAIN_COORDS_H