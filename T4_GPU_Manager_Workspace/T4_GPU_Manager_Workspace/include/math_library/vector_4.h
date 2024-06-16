#ifndef __VEC4_H__
#define __VEC4_H__ 1

#include "vector_3.h"
#include "matrix_3.h"

class Vec4
{
public:
  Vec4();
  Vec4(float x, float y, float z, float w);
  Vec4(Vec3 a, float w);
  Vec4(float a);
  Vec4(float *values_array);
  Vec4(const Vec4 &other);
  ~Vec4();

  Vec4 operator+(const Vec4 &other) const;
  Vec4 operator+(float value) const;
  void operator+=(const Vec4 &other); // was void
  void operator+=(float value); // was void
  Vec4 operator-(const Vec4 &other) const;
  Vec4 operator-(float value) const;
  void operator-=(const Vec4 &other); // was void
  void operator-=(float value); // was void

  Vec4 operator*(float value) const;
  void operator*=(float value); // was void
  Vec4 operator/(float value) const;
  void operator/=(float value); // was void
  bool operator==(const Vec4 &other);
  bool operator!=(const Vec4 &other);
  void operator=(const Vec4 &other);

  float Magnitude() const;
  void Normalize();
  Vec4 Normalized() const;
  void Scale(Vec4 scale);
  float SqrMagnitude() const;

  static float Distance(const Vec4 &a, const Vec4 &b);
  static float DotProduct(Vec4 a, Vec4 b);
  static Vec4 Lerp(const Vec4 &a, const Vec4 &b, float index);

  static const Vec4 one;
  static const Vec4 zero;

  float x;
  float y;
  float z;
  float w;
};

inline float Vec4::Magnitude() const{
  return (float)sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

inline void Vec4::Normalize()
{
  float magnitude = (float)sqrt((x * x) + (y * y) + (z * z) + (w * w));
  if (magnitude != 0.0f)
  {
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w /= magnitude;
  }
}

inline Vec4 Vec4::Normalized() const
{
  Vec4 aux;
  float magnitude = (float)sqrt((x * x) + (y * y) + (z * z) + (w * w));
  if (magnitude != 0.0f)
  {
    aux.x = x / magnitude;
    aux.y = y / magnitude;
    aux.z = z / magnitude;
    aux.w = w / magnitude;
  }
  return aux;
}

inline void Vec4::Scale(Vec4 scale)
{
  x *= scale.x;
  y *= scale.y;
  z *= scale.z;
  w *= scale.w;
}

inline float Vec4::SqrMagnitude() const
{
  return (float)((x * x) + (y * y) + (z * z) + (w * w));
}

inline float Vec4::Distance(const Vec4 &a, const Vec4 &b)
{
  return (float)sqrt(((a.x - b.x) * (a.x - b.x)) +
                     ((a.y - b.y) * (a.y - b.y)) + 
                     ((a.z - b.z) * (a.z - b.z)) +
                      (a.w - b.w) * (a.w - b.w));
}

inline float Vec4::DotProduct(Vec4 a, Vec4 b)
{
  return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

inline Vec4 Vec4::Lerp(const Vec4 &a, const Vec4 &b, float index)
{
  Vec4 aux;
  
  if (index < 0.0f)
  {
    index = 0.0f;
  }else if(index > 1.0f)
  {
    index = 1.0f;
  }

  aux.x = a.x + index * (b.x - a.x);
  aux.y = a.y + index * (b.y - a.y);
  aux.z = a.z + index * (b.z - a.z);
  aux.w = a.w + index * (b.w - a.w);

  return aux;
}

inline Vec4 Vec4::operator+(const Vec4 &other) const{
  Vec4 aux;
  aux.x = x + other.x;
  aux.y = y + other.y;
  aux.z = z + other.z;
  aux.w = w + other.w;
  return aux;
}

inline Vec4 Vec4::operator+(float value) const{
  Vec4 aux;
  aux.x = x + value;
  aux.y = y + value;
  aux.z = z + value;
  aux.w = w + value;
  return aux;
}

inline void Vec4::operator+=(const Vec4 &other){
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
}

inline void Vec4::operator+=(float value){
  x += value;
  y += value;
  z += value;
  w += value;
}

inline Vec4 Vec4::operator-(const Vec4 &other) const{
  Vec4 aux;
  aux.x = x - other.x;
  aux.y = y - other.y;
  aux.z = z - other.z;
  aux.w = w - other.w;
  return aux;
}

inline Vec4 Vec4::operator-(float value) const{
  Vec4 aux;
  aux.x = x - value;
  aux.y = y - value;
  aux.z = z - value;
  aux.w = w - value;
  return aux;
}

inline void Vec4::operator-=(const Vec4 &other){
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
}

inline void Vec4::operator-=(float value){
  x -= value;
  y -= value;
  z -= value;
  w -= value;
}

inline Vec4 Vec4::operator*(float value) const
{
  Vec4 aux;
  aux.x = x * value;
  aux.y = y * value;
  aux.z = z * value;
  aux.w = w * value;
  return aux;
}

inline void Vec4::operator*=(float value){
  x *= value;
  y *= value;
  z *= value;
  w *= value;
}

inline Vec4 Vec4::operator/(float value) const{
  Vec4 aux;
  if( value > 0.0f){
    aux.x = x / value;
    aux.y = y / value;
    aux.z = z / value;
    aux.w = w / value;
  }
  return aux;
}

inline void Vec4::operator/=(float value){
  if ( 0.0f != value){
    x /= value;
    y /= value;
    z /= value;
    w /= value;
  }
}

inline bool Vec4::operator==(const Vec4 &other){
  return (( x == other.x ) && 
          ( y == other.y) &&
          ( z == other.z) && 
          ( w == other.w));
}
inline bool Vec4::operator!=(const Vec4 &other)
{
  return (( x != other.x ) || 
          ( y != other.y) ||
          ( z != other.z) || 
          ( w != other.w));
}
inline void Vec4::operator=(const Vec4 &other)
{
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
}

#endif
