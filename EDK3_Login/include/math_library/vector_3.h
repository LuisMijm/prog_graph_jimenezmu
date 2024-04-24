#ifndef __VEC3_H__
#define __VEC3_H__ 1

#include "math_utils.h"
#include "math.h"

class Vec3
{
public:
  Vec3();
  Vec3(float value);
  Vec3(float x, float y, float z);
  Vec3(float *values_array);
  Vec3(const Vec3 &other);
  ~Vec3();

  Vec3 operator+(const Vec3 &other) const;
  Vec3 operator+(float value) const;
  Vec3 &operator+=(const Vec3 &other);
  Vec3 &operator+=(float value);
  Vec3 operator-(const Vec3 &other) const;
  Vec3 operator-(float value) const;
  Vec3 &operator-=(const Vec3 &other);
  Vec3 &operator-=(float value);
  bool operator==(const Vec3 &other) const;
  bool operator!=(const Vec3 &other) const;
  void operator=(const Vec3 &other);
  void operator=(float value);
  Vec3 operator*(float value) const;
  Vec3 &operator*=(float value);
  Vec3 operator/(float value) const;
  Vec3 &operator/=(float value);

  float Magnitude() const;
  Vec3 Normalized() const;
  void Normalize();
  float SqrMagnitude() const;
  void Scale(const Vec3 &other);

  static Vec3 Lerp(const Vec3 &a, const Vec3 &b, float t);
  static Vec3 LerpUnclamped(const Vec3 &a, const Vec3 &b, float t);
  static float DotProduct(const Vec3 &a, const Vec3 &b);
  static float Angle(const Vec3 &a, const Vec3 &b);
  static Vec3 CrossProduct(const Vec3 &a, const Vec3 &b);
  static float Distance(const Vec3 &a, const Vec3 &b);
  static Vec3 Reflect(const Vec3 &direction, const Vec3 &normal);

  static const Vec3 up;
  static const Vec3 down;
  static const Vec3 right;
  static const Vec3 left;
  static const Vec3 forward;
  static const Vec3 back;
  static const Vec3 zero;
  static const Vec3 unit;

  float x;
  float y;
  float z;
};

inline float Vec3::Magnitude() const
{
  return (float)sqrt((x * x) + (y * y) + (z * z));
}

inline void Vec3::Normalize()
{

  float Magnitude = (float)sqrt((x * x) + (y * y) + (z * z));
  if (Magnitude != 0)
  {
    x /= Magnitude;
    y /= Magnitude;
    z /= Magnitude;
  }
}

inline Vec3 Vec3::Normalized() const
{
  Vec3 aux;
  float Magnitude = (float)sqrt((x * x) + (y * y) + (z * z));
  if (Magnitude != 0)
  {
    aux.x = x / Magnitude;
    aux.y = y / Magnitude;
    aux.z = z / Magnitude;
  }
  return aux;
}

inline float Vec3::DotProduct(const Vec3 &a, const Vec3 &other){
  return ((a.x * other.x) + (a.y * other.y) + (a.z * other.z));
}

inline float Vec3::Angle(const Vec3 &a, const Vec3 &other){
  float MagnitudeA = (float)sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
  float MagnitudeB = (float)sqrt((other.x * other.x) + (other.y * other.y) + (other.z * other.z));
  float MagnitudeTotal = MagnitudeA * MagnitudeB;
  if ( MagnitudeTotal == 0){
    return 0.0f;
  }else{
    return (float)acos(((a.x * other.x) + (a.y * other.y) + (a.z * other.z))/ MagnitudeTotal);
  }
}

inline Vec3 Vec3::CrossProduct(const Vec3 &a, const Vec3 &other)
{
  Vec3 aux;

  aux.x = (a.y * other.z) - (a.z * other.y);
  aux.y = (a.z * other.x) - (a.x * other.z);
  aux.z = (a.x * other.y) - (a.y * other.x);

  return aux;
}

inline float Vec3::SqrMagnitude() const
{
  return (float)((x * x) + (y * y) + (z * z));
}

inline void Vec3::Scale(const Vec3 &other)
{
  x *= other.x;
  y *= other.y;
  z *= other.z;
}

inline Vec3 Vec3::Lerp(const Vec3 &a, const Vec3 &b, float t)
{
  Vec3 aux;

  if (t < 0.0f)
  {
    t = 0.0f;
  }else if (t > 1)
  {
    t = 1.0f;
  }
  
  aux.x = a.x + t * (b.x - a.x);
  aux.y = a.y + t * (b.y - a.y);
  aux.z = a.z + t * (b.z - a.z);

  return aux;
}

inline Vec3 Vec3::LerpUnclamped(const Vec3 &a, const Vec3 &b, float t)
{
  Vec3 aux;

  aux.x = a.x + t * (b.x - a.x);
  aux.y = a.y + t * (b.y - a.y);
  aux.z = a.z + t * (b.z - a.z);

  return aux;
}

inline float Vec3::Distance(const Vec3 &a, const Vec3 &b)
{

  return (float)sqrt(((a.x - b.x) * (a.x - b.x)) +
                     ((a.y - b.y) * (a.y - b.y)) + 
                     ((a.z - b.z) * (a.z - b.z)));
}

inline Vec3 Vec3::Reflect(const Vec3 &direction, const Vec3 &normal)
{
  Vec3 aux;

  float dotproduct = (direction.x * normal.x) +
                     (direction.y * normal.y) +
                     (direction.z * normal.z);

  aux.x = direction.x - ((2.0f * dotproduct) * normal.x);
  aux.y = direction.y - ((2.0f * dotproduct) * normal.y);
  aux.z = direction.z - ((2.0f * dotproduct) * normal.z);

  return aux;
}

inline Vec3 Vec3::operator+(const Vec3 &other) const
{
  Vec3 aux;
  aux.x = x + other.x;
  aux.y = y + other.y;
  aux.z = z + other.z;
  return aux;
}

inline Vec3 Vec3::operator+(float value) const
{
  Vec3 aux;
  aux.x = x + value;
  aux.y = y + value;
  aux.z = z + value;
  return aux;
}

inline Vec3 &Vec3::operator+=(const Vec3 &other)
{
  x = x + other.x;
  y = y + other.y;
  z = z + other.z;
  return *this;
}

inline Vec3 &Vec3::operator+=(float value)
{
  x = x + value;
  y = y + value;
  z = z + value;
  return *this;
}

inline Vec3 Vec3::operator-(const Vec3 &other) const
{
  Vec3 aux;
  aux.x = x - other.x;
  aux.y = y - other.y;
  aux.z = z - other.z;
  return aux;
}

inline Vec3 Vec3::operator-(float value) const
{
  Vec3 aux;
  aux.x = x - value;
  aux.y = y - value;
  aux.z = z - value;
  return aux;
}

inline Vec3 &Vec3::operator-=(const Vec3 &other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

inline Vec3 &Vec3::operator-=(float value)
{
  x -= value;
  y -= value;
  z -= value;
  return *this;
}

inline bool Vec3::operator==(const Vec3 &other) const
{
  return ((x == other.x) && (y == other.y) && (z == other.z));
}

inline bool Vec3::operator!=(const Vec3 &other) const
{
  return ((x != other.x) || (y != other.y) || (z != other.z));
}

inline void Vec3::operator=(const Vec3 &other)
{
  x = other.x;
  y = other.y;
  z = other.z;
}

inline void Vec3::operator=(float value)
{
  x = value;
  y = value;
  z = value;
}

inline Vec3 Vec3::operator*(float value) const
{
  Vec3 aux;
  aux.x = x * value;
  aux.y = y * value;
  aux.z = z * value;
  return aux;
}

inline Vec3 &Vec3::operator*=(float value)
{
  x *= value;
  y *= value;
  z *= value;
  return *this;
}

inline Vec3 Vec3::operator/(float value) const
{
  Vec3 aux;
  if (value != 0.0f)
  {
    aux.x = x / value;
    aux.y = y / value;
    aux.z = z / value;
    return aux;
  }else{
    return *this;
  }
}

inline Vec3 &Vec3::operator/=(float value)
{
  if (value != 0.0f)
  {
    x /= value;
    y /= value;
    z /= value;
  }
  return *this;
}

#endif
