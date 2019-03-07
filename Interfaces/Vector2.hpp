/*
** Vector2.hpp for cpp_arcade in
**
** Made by julien1.benoit@epitech.eu
** Login   <julien1.benoit@epitech.net>
**
** Started on  lun. avr. 19:46 2017 benoit_g
** Last update lun. avr. 19:46 2017 benoit_g
*/

#ifndef CPP_ARCADE_VECTOR2_HPP
#define CPP_ARCADE_VECTOR2_HPP

#include <cmath>
#include <iostream>

template<typename T = int>
class Vector2
{
 public:
  T x;
  T y;

  Vector2() : x(0), y(0)
  {}

  Vector2(const T &_x, const T &_y) : x(_x), y(_y)
  {}

  Vector2(const Vector2 &vec) : x(vec.x), y(vec.y)
  {}

  Vector2(Vector2 &&vec) : x(vec.x), y(vec.y)
  {}

  ~Vector2()
  {}

  Vector2 &operator=(const Vector2 &vec)
  {
    this->x = vec.x;
    this->y = vec.y;
    return (*this);
  }

  Vector2 &operator=(Vector2 &&vec)
  {
    this->x = vec.x;
    this->y = vec.y;
    return (*this);
  }

  void operator+=(const Vector2 &vec)
  {
    this->x += vec.x;
    this->y += vec.y;
  }

  void operator+=(const T &val)
  {
    this->x += val;
    this->y += val;
  }

  void operator-=(const Vector2 &vec)
  {
    this->x -= vec.x;
    this->y -= vec.y;
  }

  void operator-=(const T &val)
  {
    this->x -= val;
    this->y -= val;
  }

  void operator*=(const Vector2 &vec)
  {
    this->x *= vec.x;
    this->y *= vec.y;
  }

  void operator*=(const T &val)
  {
    this->x *= val;
    this->y *= val;
  }

  void operator/=(const Vector2 &vec)
  {
    if (vec.x != 0 && vec.y != 0)
      {
	this->x /= vec.x;
	this->y /= vec.y;
      }
  }

  void operator/=(const T &val)
  {
    if (val != 0)
      {
	this->x /= val;
	this->y /= val;
      }
  }

  double magnitude(void) const
  {
    double posx = this->x * this->x;
    double posy = this->y * this->y;
    double res = sqrt(posx + posy);

    return (res < 0) ? res * -1 : res;
  }

  static double distance(const Vector2 &vec1, const Vector2 &vec2)
  {
    double posx = pow(vec1.x - vec2.x, 2);
    double posy = pow(vec1.y - vec2.y, 2);
    double res = sqrt(posx + posy);

    return (res < 0) ? res * -1 : res;
  }

  static Vector2 scale(const Vector2 &vec1, const Vector2 &vec2)
  {
    return (Vector2(vec1.x * vec2.x, vec1.y * vec2.y));
  }
};

template<typename T = int>
std::ostream &operator<<(std::ostream &os, const Vector2<T> &vec)
{
  os << "x = " << vec.x << "  y = " << vec.y;
  return (os);
}

template<typename T = int>
Vector2<T> operator+(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
  return Vector2<T>(vec1.x + vec2.x, vec1.y + vec2.y);
}

template<typename T = int>
Vector2<T> operator+(const Vector2<T> &vec, const T &val)
{
  return Vector2<T>(vec.x + val, vec.y + val);
}

template<typename T = int>
Vector2<T> operator+(const T &val, const Vector2<T> &vec)
{
  return Vector2<T>(vec.x + val, vec.y + val);
}

template<typename T = int>
Vector2<T> operator-(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
  return Vector2<T>(vec1.x - vec2.x, vec1.y - vec2.y);
}

template<typename T = int>
Vector2<T> operator-(const Vector2<T> &vec, const T &val)
{
  return Vector2<T>(vec.x - val, vec.y - val);
}

template<typename T = int>
Vector2<T> operator-(const T &val, const Vector2<T> &vec)
{
  return Vector2<T>(val - vec.x, val - vec.y);
}

template<typename T = int>
Vector2<T> operator-(const Vector2<T> &vec)
{
  return Vector2<T>(vec.x * -1, vec.y * -1);
}

template<typename T = int>
Vector2<T> operator*(const Vector2<T> &vec, const T &val)
{
  return Vector2<T>(vec.x * val, vec.y * val);
}

template<typename T = int>
Vector2<T> operator*(const T &val, const Vector2<T> &vec)
{
  return Vector2<T>(vec.x * val, vec.y * val);
}

template<typename T = int>
Vector2<T> operator/(const Vector2<T> &vec, const T &val)
{
  if (val != 0)
    return Vector2<T>(vec.x / val, vec.y / val);
  return Vector2<T>();
}

template<typename T = int>
bool operator==(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
  return (vec1.x == vec2.x && vec1.y == vec2.y);
}

template<typename T = int>
bool operator!=(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
  return (vec1.x != vec2.x && vec1.y != vec2.y);
}

#endif /* !CPP_ARCADE_VECTOR2_HPP */
