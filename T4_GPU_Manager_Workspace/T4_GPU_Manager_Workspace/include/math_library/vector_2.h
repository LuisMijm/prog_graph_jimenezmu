//--------------------------------------------------------------//
//  Math Library
//  Vector 2 Class.
//--------------------------------------------------------------//

#ifndef __VEC2_H__
#define __VEC2_H__ 1

#include "math.h"
/// @class Vec2 vector2.h "vector2.h"
/// @brief Basic float vector 2.
class Vec2
{
public:
  Vec2();
  Vec2(float x, float y);
  Vec2(const Vec2 &copy);
  ~Vec2();

  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator+(float value);
  Vec2 &operator+=(const Vec2 &other);
  Vec2 &operator+=(float value);
  Vec2 operator-(const Vec2 &other) const; // Vec2 v = a - b;
  Vec2 operator-(float value) const;       // Vec2 v = a - 3.0f;
  Vec2 operator-() const;                  // Vec2 v = -a;
  Vec2 &operator-=(const Vec2 &other);
  Vec2 &operator-=(float value);
  bool operator==(const Vec2 &other) const;
  bool operator!=(const Vec2 &other) const;
  void operator=(const Vec2 &other);
  void operator=(float value);
  Vec2 operator*(float value) const;
  Vec2 &operator*=(float value);
  Vec2 operator/(float value) const;
  Vec2 &operator/=(float value);

  float Magnitude() const;

  /// @brief Normalizes the Vec2.
  void Normalize();

  /// @brief Returns a normalized version of this Vec2.
  /// @return Normalized version of this Vec2.
  Vec2 Normalized() const;

  void Scale(const Vec2 scale);

  float SqrMagnitude() const;
  static float Distance(const Vec2 a, const Vec2 b);

  static float DotProduct(Vec2 a, Vec2 b);

  static Vec2 Lerp(const Vec2 a, const Vec2 b, float t);
  static Vec2 LerpUnclamped(const Vec2 a, const Vec2 b, float t);

  static const Vec2 up;
  static const Vec2 down;
  static const Vec2 right;
  static const Vec2 left;
  static const Vec2 zero;
  static const Vec2 one;

  float x;
  float y;
};

inline Vec2 Vec2::operator+(const Vec2 &other) const
{
  Vec2 aux;
  aux.x = x + other.x;
  aux.y = y + other.y;
  return aux;
}

inline Vec2 Vec2::operator+(float value)
{
  Vec2 aux;
  aux.x = value + x;
  aux.y = value + y;
  return aux;
}

inline Vec2 &Vec2::operator+=(const Vec2 &other)
{
  x = x + other.x;
  y = y + other.y;
  return *this;
}

inline Vec2 &Vec2::operator+=(float value)
{
  x += value;
  y += value;
  return *this;
}

inline Vec2 Vec2::operator-(const Vec2 &other) const
{
  Vec2 ret;
  ret.x = x - other.x;
  ret.y = y - other.y;
  return ret;
}

inline Vec2 Vec2::operator-(float value) const
{
  Vec2 ret;
  ret.x = x - value;
  ret.y = y - value;
  return ret;
}

inline Vec2 Vec2::operator-() const
{
  Vec2 ret;
  ret.x = -x;
  ret.y = -y;
  return ret;
}

inline Vec2 &Vec2::operator-=(const Vec2 &other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

inline Vec2 &Vec2::operator-=(float value)
{
  x -= value;
  y -= value;
  return *this;
}

inline bool Vec2::operator==(const Vec2 &value) const
{
  return ((x == value.x) && (y == value.y));
}

inline bool Vec2::operator!=(const Vec2 &value) const
{
  return ((x != value.x) || (y != value.y));
}

inline void Vec2::operator=(const Vec2 &other)
{
  x = other.x;
  y = other.y;
}

inline void Vec2::operator=(float value)
{
  x = value;
  y = value;
}

inline Vec2 Vec2::operator*(float value) const
{
  Vec2 aux;
  aux.x = x * value;
  aux.y = y * value;
  return aux;
}

inline Vec2 &Vec2::operator*=(float value)
{
  x *= value;
  y *= value;
  return *this;
}

inline Vec2 Vec2::operator/(float value) const
{
  Vec2 aux;
  if (value != 0)
  {
    aux.x = x / value;
    aux.y = y / value;
  }
  else
  {
    aux.x = x;
    aux.y = y;
  }
  return aux;
}

inline Vec2 &Vec2::operator/=(float value)
{
  if (value != 0)
  {
    x /= value;
    y /= value;
  }
  return *this;
}

inline float Vec2::Magnitude() const
{
  return (float)sqrt((x * x) + (y * y));
}

inline void Vec2::Normalize()
{
  float magnitude = (float)sqrt((x * x) + (y * y));
  if (magnitude != 0)
  {
    x /= magnitude;
    y /= magnitude;
  }
}

inline Vec2 Vec2::Normalized() const
{
  Vec2 aux;
  float magnitude = (float)sqrt((x * x) + (y * y));
  if (magnitude != 0)
  {
    aux.x = x / magnitude;
    aux.y = y / magnitude;
  }
  return aux;
}

inline void Vec2::Scale(const Vec2 scale)
{
  x *= scale.x;
  y *= scale.y;
}

inline float Vec2::SqrMagnitude() const
{
  return ((x * x) + (y * y));
}

inline float Vec2::Distance(const Vec2 a, const Vec2 b)
{
  Vec2 aux;
  aux.x = b.x - a.x;
  aux.y = b.y - a.y;
  return (float)sqrt((aux.x * aux.x) + (aux.y * aux.y));
}

inline Vec2 Vec2::Lerp(const Vec2 a, const Vec2 b, float t)
{
  if (t < 0)
  {
    t = 0.0f;
  }
  else if (t > 1)
  {
    t = 1.0f;
  }
  Vec2 aux;
  aux.x = a.x + (b.x - a.x) * t;
  aux.y = a.y + (b.y - a.y) * t;
  return aux;
}

inline Vec2 Vec2::LerpUnclamped(const Vec2 a, const Vec2 b, float t)
{
  Vec2 aux;
  aux.x = a.x + (b.x - a.x) * t;
  aux.y = a.y + (b.y - a.y) * t;
  return aux;
}

inline float Vec2::DotProduct(Vec2 a, Vec2 b)
{
  return ((a.x * b.x) + (a.y * b.y));
}

#endif
