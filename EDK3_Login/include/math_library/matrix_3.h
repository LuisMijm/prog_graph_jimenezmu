//--------------------------------------------------------------//
//  Math Library
//  Matrix 3 Class Definition.
//--------------------------------------------------------------//
//
//   m0 m3 m6
//   m1 m4 m7
//   m2 m5 m8
//
//--------------------------------------------------------------//
#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"
#include <assert.h>
#include <stdio.h>

class Mat3 {
public:

	Mat3();
	Mat3(float *values_array);
	Mat3(float value);
	Mat3(Vec3 a, Vec3 b, Vec3 c);

	Mat3(const Mat3& copy);
	~Mat3();

	static Mat3 Identity();

	Mat3 Multiply(const Mat3& other) const;

	float Determinant() const;

	Mat3 Adjoint() const;
	bool GetInverse(Mat3& out) const;
	bool Inverse();

	Mat3 Transpose() const;

	static Mat3 Translate(const Vec2& position);
	static Mat3 Translate(float x, float y);
  static Mat3 Rotate(float rotation);
  static Mat3 Scale(const Vec2& scale);
  static Mat3 Scale(float x, float y);

	Vec3 GetColumn(int colum) const;
	Vec3 GetLine(int line) const;

	inline Mat3 operator+(const Mat3& other) const;
	inline Mat3& operator+=(const Mat3& other);
	inline Mat3 operator+(float value) const;
	inline Mat3& operator+=(float value);
	inline Mat3 operator-(const Mat3& other) const;
	inline Mat3& operator-=(const Mat3& other);
	inline Mat3 operator-(float value) const;
	inline Mat3& operator-=(float value);
	inline Mat3 operator*(float value) const;
	inline Mat3& operator*=(float value);
	inline Mat3 operator/(float value) const;
	inline Mat3& operator/=(float value);
	bool operator==(const Mat3& other) const;
	bool operator!=(const Mat3& other) const;
	inline void operator=(const Mat3& other);
	
	void print();
  Vec3 TransformVec3(const Vec3& vec);
  Vec2 TransformVec2(const Vec2& vec);

	float m[9];
};

inline void Mat3::print(){
	printf("%f %f %f \n", m[0],m[3],m[6]);
	printf("%f %f %f \n", m[1],m[4],m[7]);
	printf("%f %f %f \n", m[2],m[5],m[8]);
}

inline Mat3 Mat3::operator+(const Mat3& other) const {
	Mat3 aux;
	aux.m[0] = m[0] + other.m[0];
	aux.m[1] = m[1] + other.m[1];
	aux.m[2] = m[2] + other.m[2];
	
	aux.m[3] = m[3] + other.m[3];
	aux.m[4] = m[4] + other.m[4];
	aux.m[5] = m[5] + other.m[5];

	aux.m[6] = m[6] + other.m[6];
	aux.m[7] = m[7] + other.m[7];
	aux.m[8] = m[8] + other.m[8];
	
	return aux;
}

inline Mat3& Mat3::operator+=(const Mat3& other) {
	m[0] += other.m[0];
	m[1] += other.m[1];
	m[2] += other.m[2];

	m[3] += other.m[3];
	m[4] += other.m[4];
	m[5] += other.m[5];

	m[6] += other.m[6];
	m[7] += other.m[7];
	m[8] += other.m[8];

	return (*this);
}

inline Mat3 Mat3::operator+(float value) const {
	Mat3 aux;
	aux.m[0] = m[0] + value;
	aux.m[1] = m[1] + value;
	aux.m[2] = m[2] + value;

	aux.m[3] = m[3] + value;
	aux.m[4] = m[4] + value;
	aux.m[5] = m[5] + value;

	aux.m[6] = m[6] + value;
	aux.m[7] = m[7] + value;
	aux.m[8] = m[8] + value;
	return aux;
}

inline Mat3& Mat3::operator+=(float value) {
	m[0] += value;
	m[1] += value;
	m[2] += value;

	m[3] += value;
	m[4] += value;
	m[5] += value;

	m[6] += value;
	m[7] += value;
	m[8] += value;
	return (*this);
}

inline Mat3 Mat3::operator-(const Mat3& other) const {
	Mat3 aux;
	aux.m[0] = m[0] - other.m[0];
	aux.m[1] = m[1] - other.m[1];
	aux.m[2] = m[2] - other.m[2];

	aux.m[3] = m[3] - other.m[3];
	aux.m[4] = m[4] - other.m[4];
	aux.m[5] = m[5] - other.m[5];

	aux.m[6] = m[6] - other.m[6];
	aux.m[7] = m[7] - other.m[7];
	aux.m[8] = m[8] - other.m[8];
	return aux;
}

inline Mat3& Mat3::operator-=(const Mat3& other) {
	m[0] -= other.m[0];
	m[1] -= other.m[1];
	m[2] -= other.m[2];

	m[3] -= other.m[3];
	m[4] -= other.m[4];
	m[5] -= other.m[5];

	m[6] -= other.m[6];
	m[7] -= other.m[7];
	m[8] -= other.m[8];
	return (*this);
}

inline Mat3 Mat3::operator-(float value) const {
	Mat3 aux;
	aux.m[0] = m[0] - value;
	aux.m[1] = m[1] - value;
	aux.m[2] = m[2] - value;

	aux.m[3] = m[3] - value;
	aux.m[4] = m[4] - value;
	aux.m[5] = m[5] - value;

	aux.m[6] = m[6] - value;
	aux.m[7] = m[7] - value;
	aux.m[8] = m[8] - value;
	return aux;
}

inline Mat3& Mat3::operator-=(float value) {
	m[0] -= value;
	m[1] -= value;
	m[2] -= value;

	m[3] -= value;
	m[4] -= value;
	m[5] -= value;

	m[6] -= value;
	m[7] -= value;
	m[8] -= value;
	return (*this);
}

inline Mat3 Mat3::operator*(float value) const {
	Mat3 aux;
	aux.m[0] = m[0] * value;
	aux.m[1] = m[1] * value;
	aux.m[2] = m[2] * value;

	aux.m[3] = m[3] * value;
	aux.m[4] = m[4] * value;
	aux.m[5] = m[5] * value;

	aux.m[6] = m[6] * value;
	aux.m[7] = m[7] * value;
	aux.m[8] = m[8] * value;

	return aux;
}

inline Mat3& Mat3::operator*=(float value) {
	m[0] *= value;
	m[1] *= value;
	m[2] *= value;

	m[3] *= value;
	m[4] *= value;
	m[5] *= value;

	m[6] *= value;
	m[7] *= value;
	m[8] *= value;
	return (*this);
}

inline Mat3 Mat3::operator/(float value) const {
	Mat3 aux;
	assert( value != 0);
	aux.m[0] = m[0] / value;
	aux.m[1] = m[1] / value;
	aux.m[2] = m[2] / value;

	aux.m[3] = m[3] / value;
	aux.m[4] = m[4] / value;
	aux.m[5] = m[5] / value;

	aux.m[6] = m[6] / value;
	aux.m[7] = m[7] / value;
	aux.m[8] = m[8] / value;

	return aux;
}

inline Mat3& Mat3::operator/=(float value) {
	assert( value != 0);
	m[0] /= value;
	m[1] /= value;
	m[2] /= value;

	m[3] /= value;
	m[4] /= value;
	m[5] /= value;

	m[6] /= value;
	m[7] /= value;
	m[8] /= value;
	return (*this);
}

inline bool Mat3::operator==(const Mat3& other) const {
  return (m[0] == other.m[0]) &&
         (m[1] == other.m[1]) &&
         (m[2] == other.m[2]) &&

         (m[3] == other.m[3]) &&
         (m[4] == other.m[4]) &&
         (m[5] == other.m[5]) &&

         (m[6] == other.m[6]) &&
         (m[7] == other.m[7]) &&
         (m[8] == other.m[8]);
}

inline bool Mat3::operator!=(const Mat3& other) const {
  return (m[0] != other.m[0]) ||
         (m[1] != other.m[1]) ||
         (m[2] != other.m[2]) ||

         (m[3] != other.m[3]) ||
         (m[4] != other.m[4]) ||
         (m[5] != other.m[5]) ||

         (m[6] != other.m[6]) ||
         (m[7] != other.m[7]) ||
         (m[8] != other.m[8]);
}

inline void Mat3::operator=(const Mat3& other) {
  m[0] = other.m[0];
  m[1] = other.m[1];
  m[2] = other.m[2];

  m[3] = other.m[3];
  m[4] = other.m[4];
  m[5] = other.m[5];

  m[6] = other.m[6];
  m[7] = other.m[7];
  m[8] = other.m[8];
}

inline Mat3 Mat3::Identity() {
  Mat3 aux;
  aux.m[0] = 1.0f; aux.m[3] = 0.0f; aux.m[6] = 0.0f;
  aux.m[1] = 0.0f; aux.m[4] = 1.0f; aux.m[7] = 0.0f;
  aux.m[2] = 0.0f; aux.m[5] = 0.0f; aux.m[8] = 1.0f;

  return aux;
}

inline float Mat3::Determinant() const {
  return (((m[0] * m[4] * m[8]) + 
         (m[1] * m[5] * m[6]) + 
         (m[2] * m[3] * m[7])) 
         - 
         ((m[6] * m[4] * m[2]) + 
         (m[7] * m[5] * m[0]) + 
         (m[1] * m[3] * m[8])));
}

inline bool Mat3::GetInverse(Mat3& out) const {
  float det = this->Determinant();
  if ( det != 0){
    out = this->Adjoint();
    out /= det;
    return true;
  }else{
    return false;
  }
}

inline bool Mat3::Inverse() {
  float det = this->Determinant();
	if ( det != 0){
    *this = this->Adjoint();
    *this /= det;
    return true;
  }else{
    return false;
  }
}

inline Mat3 Mat3::Multiply(const Mat3& other) const {
  Mat3 aux;
  aux.m[0] = (m[0] * other.m[0]) + (m[3] * other.m[1]) + (m[6] * other.m[2]);
  aux.m[1] = (m[1] * other.m[0]) + (m[4] * other.m[1]) + (m[7] * other.m[2]);
  aux.m[2] = (m[2] * other.m[0]) + (m[5] * other.m[1]) + (m[8] * other.m[2]);

  aux.m[3] = (m[0] * other.m[3]) + (m[3] * other.m[4]) + (m[6] * other.m[5]);
  aux.m[4] = (m[1] * other.m[3]) + (m[4] * other.m[4]) + (m[7] * other.m[5]);
  aux.m[5] = (m[2] * other.m[3]) + (m[5] * other.m[4]) + (m[8] * other.m[5]);
 
  aux.m[6] = (m[0] * other.m[6]) + (m[3] * other.m[7]) + (m[6] * other.m[8]);
  aux.m[7] = (m[1] * other.m[6]) + (m[4] * other.m[7]) + (m[7] * other.m[8]);
  aux.m[8] = (m[2] * other.m[6]) + (m[5] * other.m[7]) + (m[8] * other.m[8]);

	return aux;
}

inline Mat3 Mat3::Adjoint() const {
  Mat3 aux;
  aux.m[0] = ((m[4] * m[8]) - (m[5] * m[7]));
  aux.m[1] = -1.0f * ((m[3] * m[8]) - (m[5] * m[6]));
  aux.m[2] = ((m[3] * m[7]) - (m[4] * m[6]));
  aux.m[3] = -1.0f * ((m[1] * m[8]) - (m[2] * m[7]));
  aux.m[4] = ((m[0] * m[8]) - (m[2] * m[6]));
  aux.m[5] = -1.0f * ((m[0] * m[7]) - (m[1] * m[6]));
  aux.m[6] = ((m[1] * m[5]) - (m[2] * m[4]));
  aux.m[7] = -1.0f * ((m[0] * m[5]) - (m[2] * m[3]));
  aux.m[8] = ((m[0] * m[4]) - (m[3] * m[1]));
//   return aux;
  return aux.Transpose();
}

inline Mat3 Mat3::Transpose() const {
  Mat3 aux;
  aux.m[0] = m[0];
  aux.m[1] = m[3];
  aux.m[2] = m[6];

  aux.m[3] = m[1];
  aux.m[4] = m[4];
  aux.m[5] = m[7];
  
  aux.m[6] = m[2];
  aux.m[7] = m[5];
  aux.m[8] = m[8];
	return aux;
}

inline Vec3 Mat3::GetColumn(int colum) const {
	Vec3 aux;

  aux.x = m[colum*3];
  aux.y = m[colum*3 + 1];
  aux.z = m[colum*3 + 2];

  return aux;
}

inline Vec3 Mat3::GetLine(int line) const {
  Vec3 aux;
  aux.x = m[line];
  aux.y = m[line + 3];
  aux.z = m[line + 6];
	return aux;
}

inline Vec3 Mat3::TransformVec3(const Vec3& vec) {
  float c[3] = { vec.x, vec.y, vec.z };
  float r[3] = {
    m[0] * c[0] + m[3] * c[1] + m[6] * c[2],
    m[1] * c[0] + m[4] * c[1] + m[7] * c[2],
    m[2] * c[0] + m[5] * c[1] + m[8] * c[2]};
  Vec3 k;
  k.x = r[0];
  k.y = r[1];
  k.z = r[2];
  return k;
}

inline Vec2 Mat3::TransformVec2(const Vec2& vec) {
  Vec3 tmp = { vec.x, vec.y, 1.0 };
  Vec3 result = TransformVec3(tmp);
  result.x = result.x/result.z;
  result.y = result.y/result.z;
  Vec2 k;
  k.x = result.x;
  k.y = result.y;
  return k;
}
#endif 
