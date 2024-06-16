#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"
#include <stdio.h>
class Mat4 {
 public:

  Mat4();
  Mat4(float a[16]);
  Mat4(const float a[16]);
  Mat4(float value);
  Mat4(const Mat4& copy);
  ~Mat4();

  static Mat4 Identity();
  Mat4 Multiply(const Mat4& other) const;

  float Determinant() const;
  Mat4 Adjoint() const;

  Vec4 TransformVec4(const Vec4 &v);
	Vec3 TransformVec3(const Vec3 &r);

  bool GetInverse(Mat4* out) const;
  bool Inverse();

  Mat4 Transpose() const;

  static Mat4 Translate(const Vec3& distance);
  static Mat4 Translate(float x, float y, float z);

  static Mat4 Scale(const Vec3& scale);
  static Mat4 Scale(float x, float y, float z);

  static Mat4 RotateX(float radians);
  static Mat4 RotateY(float radians);
  static Mat4 RotateZ(float radians);

  static Mat4 GetTransform(const Vec3& translate, const Vec3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Mat4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Mat4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Mat4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  Vec4 GetColumn(int colum) const;
  Vec4 GetLine(int line) const;

  Mat4 operator+(const Mat4& other) const;
  Mat4& operator+=(const Mat4& other);
  Mat4 operator+(float value) const;
  Mat4& operator+=(float value);
  Mat4 operator-(const Mat4& other) const;
  Mat4& operator-=(const Mat4& other);
  Mat4 operator-(float value) const;
  Mat4& operator-=(float value);
  Mat4& operator*=(float value);
  Mat4 operator*(float value) const;
  Mat4& operator/=(float value);
  Mat4 operator/(float value) const;
  bool operator==(const Mat4& other);
  bool operator!=(const Mat4& other);
  void operator=(const Mat4& other);
  void print();
  float m[16];
};

inline void Mat4::print(){
  printf("%f, %f, %f, %f\n",m[0], m[4], m[8], m[12]);
  printf("%f, %f, %f, %f\n",m[1], m[5], m[9], m[13]);
  printf("%f, %f, %f, %f\n",m[2], m[6], m[10], m[14]);
  printf("%f, %f, %f, %f\n",m[3], m[7], m[11], m[15]);
}

inline Mat4 Mat4::Identity() {
  Mat4 aux;
  aux.m[0] = 1.0f; aux.m[4] = 0.0f; aux.m[8] =  0.0f; aux.m[12] = 0.0f;
  aux.m[1] = 0.0f; aux.m[5] = 1.0f; aux.m[9] =  0.0f; aux.m[13] = 0.0f;
  aux.m[2] = 0.0f; aux.m[6] = 0.0f; aux.m[10] = 1.0f; aux.m[14] = 0.0f;
  aux.m[3] = 0.0f; aux.m[7] = 0.0f; aux.m[11] = 0.0f; aux.m[15] = 1.0f;
	return aux;
}

inline Mat4 Mat4::Multiply(const Mat4& other)const  {
  Mat4 aux;
  aux.m[0]  = (m[0] * other.m[0])  + (m[4] * other.m[1])  + (m[8]  * other.m[2])  + (m[12] * other.m[3]);
  aux.m[1]  = (m[1] * other.m[0])  + (m[5] * other.m[1])  + (m[9]  * other.m[2])  + (m[13] * other.m[3]);
  aux.m[2]  = (m[2] * other.m[0])  + (m[6] * other.m[1])  + (m[10] * other.m[2])  + (m[14] * other.m[3]);
  aux.m[3]  = (m[3] * other.m[0])  + (m[7] * other.m[1])  + (m[11] * other.m[2])  + (m[15] * other.m[3]);
  aux.m[4]  = (m[0] * other.m[4])  + (m[4] * other.m[5])  + (m[8]  * other.m[6])  + (m[12] * other.m[7]);
  aux.m[5]  = (m[1] * other.m[4])  + (m[5] * other.m[5])  + (m[9]  * other.m[6])  + (m[13] * other.m[7]);
  aux.m[6]  = (m[2] * other.m[4])  + (m[6] * other.m[5])  + (m[10] * other.m[6])  + (m[14] * other.m[7]);
  aux.m[7]  = (m[3] * other.m[4])  + (m[7] * other.m[5])  + (m[11] * other.m[6])  + (m[15] * other.m[7]);
  aux.m[8]  = (m[0] * other.m[8])  + (m[4] * other.m[9])  + (m[8]  * other.m[10]) + (m[12] * other.m[11]);
  aux.m[9]  = (m[1] * other.m[8])  + (m[5] * other.m[9])  + (m[9]  * other.m[10]) + (m[13] * other.m[11]);
  aux.m[10] = (m[2] * other.m[8])  + (m[6] * other.m[9])  + (m[10] * other.m[10]) + (m[14] * other.m[11]);
  aux.m[11] = (m[3] * other.m[8])  + (m[7] * other.m[9])  + (m[11] * other.m[10]) + (m[15] * other.m[11]);
  aux.m[12] = (m[0] * other.m[12]) + (m[4] * other.m[13]) + (m[8]  * other.m[14]) + (m[12] * other.m[15]);
  aux.m[13] = (m[1] * other.m[12]) + (m[5] * other.m[13]) + (m[9]  * other.m[14]) + (m[13] * other.m[15]);
  aux.m[14] = (m[2] * other.m[12]) + (m[6] * other.m[13]) + (m[10] * other.m[14]) + (m[14] * other.m[15]);
  aux.m[15] = (m[3] * other.m[12]) + (m[7] * other.m[13]) + (m[11] * other.m[14]) + (m[15] * other.m[15]);
	return aux;
}

inline float Mat4::Determinant() const {
  
  float det1 = Mat3({m[5],m[6],m[7]},{m[9],m[10],m[11]},{m[13],m[14],m[15]}).Determinant();
  float det2 = Mat3({m[4],m[6],m[7]},{m[8],m[10],m[11]},{m[12],m[14],m[15]}).Determinant();
  float det3 = Mat3({m[4],m[5],m[7]},{m[8],m[9],m[11]},{m[12],m[13],m[15]}).Determinant();
  float det4 = Mat3({m[4],m[5],m[6]},{m[8],m[9],m[10]},{m[12],m[13],m[14]}).Determinant();
  return ((m[0]*det1) + (-1.0f*(m[1] * det2)) + (m[2] * det3 ) + ( -1.0f *(m[3] * det4)));
}

inline Mat4 Mat4::Adjoint() const {
	Mat4 aux;
  aux.m[0]  = Mat3({m[5],m[6],m[7]},{m[9],m[10],m[11]},{m[13],m[14],m[15]}).Determinant();         //ok 
  aux.m[1]  = -1.0f * Mat3({m[4],m[6],m[7]},{m[8],m[10],m[11]},{m[12],m[14],m[15]}).Determinant(); //ok
  aux.m[2]  = Mat3({m[4],m[5],m[7]},{m[8],m[9],m[11]},{m[12],m[13],m[15]}).Determinant();          //ok
  aux.m[3]  = -1.0f * Mat3({m[4],m[5],m[6]},{m[8],m[9],m[10]},{m[12],m[13],m[14]}).Determinant();  //ok

  aux.m[4]  = -1.0f * Mat3({m[1],m[2],m[3]},{m[9],m[10],m[11]},{m[13],m[14],m[15]}).Determinant();         //ok 
  aux.m[5]  = Mat3({m[0],m[2],m[3]},{m[8],m[10],m[11]},{m[12],m[14],m[15]}).Determinant(); //ok
  aux.m[6]  = -1.0f * Mat3({m[0],m[1],m[3]},{m[8],m[9],m[11]},{m[12],m[13],m[15]}).Determinant();          //ok
  aux.m[7]  = Mat3({m[0],m[1],m[2]},{m[8],m[9],m[10]},{m[12],m[13],m[14]}).Determinant();  //ok

  aux.m[8]  = Mat3({m[1],m[2],m[3]},{m[5],m[6],m[7]},{m[13],m[14],m[15]}).Determinant();          //ok   
  aux.m[9]  = -1.0f * Mat3({m[0],m[2],m[3]},{m[4],m[6],m[7]},{m[12],m[14],m[15]}).Determinant();  //ok
  aux.m[10] = Mat3({m[0],m[1],m[3]},{m[4],m[5],m[7]},{m[12],m[13],m[15]}).Determinant();          //ok
  aux.m[11] = -1.0f * Mat3({m[0],m[1],m[2]},{m[4],m[5],m[6]},{m[12],m[13],m[14]}).Determinant();  //ok

  aux.m[12]  = -1.0f * Mat3({m[1],m[2],m[3]},{m[5],m[6],m[7]},{m[9],m[10],m[11]}).Determinant();          //ok   
  aux.m[13]  =  Mat3({m[0],m[2],m[3]},{m[4],m[6],m[7]},{m[8],m[10],m[11]}).Determinant();  //ok
  aux.m[14] = -1.0f * Mat3({m[0],m[1],m[3]},{m[4],m[5],m[7]},{m[8],m[9],m[11]}).Determinant();            //ok
  aux.m[15] = Mat3({m[0],m[1],m[2]},{m[4],m[5],m[6]},{m[8],m[9],m[10]}).Determinant();    //ok

  // return aux;
  return aux.Transpose();
}

inline Vec4 Mat4::TransformVec4(const Vec4 &v) {
  Vec4 o;
  o.x = m[0] * v.x + m[4] * v.y + m[8]  * v.z + m[12] * v.w;
  o.y = m[1] * v.x + m[5] * v.y + m[9]  * v.z + m[13] * v.w;
  o.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
  o.w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;
  return o;
}

inline Vec3 Mat4::TransformVec3(const Vec3 &r) {
  Vec4 tmp;
  tmp.x = r.x;
  tmp.y = r.y;
  tmp.z = r.z;
  tmp.w = 1.0;
  Vec4 result = TransformVec4(tmp);
  result.x = result.x / result.w;
  result.y = result.y / result.w;
  result.z = result.z / result.w;
  Vec3 k;
  k.x = result.x;
  k.y = result.y;
  k.z = result.z;
  return k;
}

inline bool Mat4::Inverse() {
  float det = Determinant();
  if (0 != det)
  {
    *this = Adjoint();
    *this /= det;
    return true;
  }else
  {
	  return false;
  }
}

inline bool Mat4::GetInverse(Mat4* out) const {
	float det = this->Determinant();
  if (0 != det)
  {
    *out = this->Adjoint();
    *out = out->Transpose(); 
    *out /= det;
    return true; 
  }else
  {
    return false;
  }
}

inline Mat4 Mat4::Transpose() const {
  /*
   [0] [4] [8]  [12]
   [1] [5] [9]  [13]
   [2] [6] [10] [14]
   [3] [7] [11] [15]
  */
	Mat4 aux;
  aux.m[0] = m[0]; aux.m[4] = m[1]; aux.m[8] = m[2];  aux.m[12] = m[3];
  aux.m[1] = m[4]; aux.m[5] = m[5]; aux.m[9] = m[6];  aux.m[13] = m[7];
  aux.m[2] = m[8]; aux.m[6] = m[9]; aux.m[10] = m[10]; aux.m[14] = m[11];
  aux.m[3] = m[12]; aux.m[7] = m[13]; aux.m[11] = m[14]; aux.m[15] = m[15];
	return aux;
}

inline Mat4 Mat4::Translate(const Vec3& distance){

  Mat4 aux = Identity();

  // aux.m[3] = distance.x;
  // aux.m[7] = distance.y;
  // aux.m[11] = distance.z;
  aux.m[12] = distance.x;
  aux.m[13] = distance.y;
  aux.m[14] = distance.z;

  return aux;
}

inline Mat4 Mat4::Translate(float x, float y, float z){

  Mat4 aux = Identity();
  // aux.m[3] = x;
  // aux.m[7] = y;
  // aux.m[11] = z;
  aux.m[12] = x; 
  aux.m[13] = y;
  aux.m[14] = z;
  return aux;
}

inline Mat4 Mat4::Scale(const Vec3& scale){
  Mat4 aux = Identity();

  aux.m[0]  = scale.x;
  aux.m[5]  = scale.y;
  aux.m[10] = scale.z;

  return aux;
}

inline Mat4 Mat4::Scale(float x, float y, float z){

  Mat4 aux = Identity();

  aux.m[0]  = x;
  aux.m[5]  = y;
  aux.m[10] = z;

  return aux;
}

inline Mat4 Mat4::RotateX(float radians){

  Mat4 aux = Identity();

  aux.m[5]  = (float)cos(radians);
  aux.m[6]  = (float)sin(radians);
  aux.m[9]  = (float)sin(radians) * -1.0f;
  aux.m[10] = (float)cos(radians);

  return aux;
}

inline Mat4 Mat4::RotateY(float radians){

  Mat4 aux = Identity();

  aux.m[0] = (float)cos(radians);
  aux.m[2] = (float)sin(radians) * -1.0f;
  aux.m[8] = (float)sin(radians);
  aux.m[10] = (float)cos(radians);

  return aux;
}

inline Mat4 Mat4::RotateZ(float radians) {

  Mat4 aux = Identity();

  aux.m[0] = (float)cos(radians);
  aux.m[1] = (float)sin(radians);
  aux.m[4] = (float)sin(radians) * -1.0f;
  aux.m[5] = (float)cos(radians);

  return aux;
}

inline Mat4 Mat4::GetTransform(const Vec3& translate,
								const Vec3& scale,
								float rotateX, float rotateY,
								float rotateZ)   {

  Mat4 temp_matrix = Mat4::Identity();


  temp_matrix = Scale(scale.x, scale.y, scale.z).Multiply(temp_matrix);
  temp_matrix = RotateX(rotateX).Multiply(temp_matrix);
  temp_matrix = RotateY(rotateY).Multiply(temp_matrix);
  temp_matrix = RotateZ(rotateZ).Multiply(temp_matrix);

  return Translate(translate.x, translate.y, translate.z).Multiply(temp_matrix);
}

inline Mat4 Mat4::GetTransform(float trans_x, float trans_y, float trans_z,
	float scale_x, float scale_y, float scale_Z,
	float rotateX, float rotateY, float rotateZ)  {

  Mat4 temp_matrix = Mat4::Identity();

  temp_matrix = Scale(scale_x, scale_y, scale_Z).Multiply(temp_matrix);
  temp_matrix = RotateX(rotateX).Multiply(temp_matrix);
  temp_matrix = RotateY(rotateY).Multiply(temp_matrix);
  temp_matrix = RotateZ(rotateZ).Multiply(temp_matrix);

  return Translate(trans_x, trans_y, trans_z).Multiply(temp_matrix);
}

inline Vec4 Mat4::GetColumn(int colum) const {
  Vec4 aux;
  aux.x = m[colum * 4];
  aux.y = m[(colum * 4) + 1];
  aux.z = m[(colum * 4) + 2];
  aux.w = m[(colum * 4) + 3];
  return aux;
}

inline Vec4 Mat4::GetLine(int line) const {
  Vec4 aux;
  aux.x = m[line];
  aux.y = m[line + 4];
  aux.z = m[line + 8];
  aux.w = m[line + 12];
  return aux;
}

inline Mat4 Mat4::PerspectiveMatrix(float fov, float aspect,
	float near, float far) const {
	
	return Mat4();
}

inline Mat4 Mat4::OrthoMatrix(float right, float left, float top, float valueottom,
	float near, float far) const {

	return Mat4();
}

inline Mat4 Mat4::operator+(const Mat4& other) const {
  Mat4 aux;
  aux.m[0]  = m[0]  + other.m[0];   
  aux.m[1]  = m[1]  + other.m[1];  
  aux.m[2]  = m[2]  + other.m[2]; 
  aux.m[3]  = m[3]  + other.m[3];  
  aux.m[4]  = m[4]  + other.m[4];
  aux.m[5]  = m[5]  + other.m[5];
  aux.m[6]  = m[6]  + other.m[6];
  aux.m[7]  = m[7]  + other.m[7];
  aux.m[8]  = m[8]  + other.m[8];
  aux.m[9]  = m[9]  + other.m[9];
  aux.m[10] = m[10] + other.m[10];
  aux.m[11] = m[11] + other.m[11];
  aux.m[12] = m[12] + other.m[12];
  aux.m[13] = m[13] + other.m[13];
  aux.m[14] = m[14] + other.m[14];
  aux.m[15] = m[15] + other.m[15];

  return aux;
}

inline Mat4& Mat4::operator+=(const Mat4& other) {
  m[0]  += other.m[0];
  m[1]  += other.m[1];
  m[2]  += other.m[2];
  m[3]  += other.m[3];
  m[4]  += other.m[4];
  m[5]  += other.m[5];
  m[6]  += other.m[6];
  m[7]  += other.m[7];
  m[8]  += other.m[8];
  m[9]  += other.m[9];
  m[10] += other.m[10];
  m[11] += other.m[11];
  m[12] += other.m[12];
  m[13] += other.m[13];
  m[14] += other.m[14];
  m[15] += other.m[15];
  return (*this);
}

inline Mat4 Mat4::operator+(float value) const {
  Mat4 aux;
  aux.m[0]  = m[0]  + value;
  aux.m[1]  = m[1]  + value;
  aux.m[2]  = m[2]  + value;
  aux.m[3]  = m[3]  + value;
  aux.m[4]  = m[4]  + value;
  aux.m[5]  = m[5]  + value;
  aux.m[6]  = m[6]  + value;
  aux.m[7]  = m[7]  + value;
  aux.m[8]  = m[8]  + value;
  aux.m[9]  = m[9]  + value;
  aux.m[10] = m[10] + value;
  aux.m[11] = m[11] + value;
  aux.m[12] = m[12] + value;
  aux.m[13] = m[13] + value;
  aux.m[14] = m[14] + value;
  aux.m[15] = m[15] + value;

  return aux;
}

inline Mat4& Mat4::operator+=(float value) {
  m[0]  += value;
  m[1]  += value;
  m[2]  += value;
  m[3]  += value;
  m[4]  += value;
  m[5]  += value;
  m[6]  += value;
  m[7]  += value;
  m[8]  += value;
  m[9]  += value;
  m[10] += value;
  m[11] += value;
  m[12] += value;
  m[13] += value;
  m[14] += value;
  m[15] += value;
  return (*this);
}

inline Mat4 Mat4::operator-(const Mat4& other) const  {
  Mat4 aux;
  aux.m[0]  = m[0]  - other.m[0];
  aux.m[1]  = m[1]  - other.m[1];
  aux.m[2]  = m[2]  - other.m[2];
  aux.m[3]  = m[3]  - other.m[3];
  aux.m[4]  = m[4]  - other.m[4];
  aux.m[5]  = m[5]  - other.m[5];
  aux.m[6]  = m[6]  - other.m[6];
  aux.m[7]  = m[7]  - other.m[7];
  aux.m[8]  = m[8]  - other.m[8];
  aux.m[9]  = m[9]  - other.m[9];
  aux.m[10] = m[10] - other.m[10];
  aux.m[11] = m[11] - other.m[11];
  aux.m[12] = m[12] - other.m[12];
  aux.m[13] = m[13] - other.m[13];
  aux.m[14] = m[14] - other.m[14];
  aux.m[15] = m[15] - other.m[15];

  return aux;
}

inline Mat4& Mat4::operator-=(const Mat4& other) {
  m[0]  -= other.m[0];
  m[1]  -= other.m[1];
  m[2]  -= other.m[2];
  m[3]  -= other.m[3];
  m[4]  -= other.m[4];
  m[5]  -= other.m[5];
  m[6]  -= other.m[6];
  m[7]  -= other.m[7];
  m[8]  -= other.m[8];
  m[9]  -= other.m[9];
  m[10] -= other.m[10];
  m[11] -= other.m[11];
  m[12] -= other.m[12];
  m[13] -= other.m[13];
  m[14] -= other.m[14];
  m[15] -= other.m[15];
  return (*this);
}

inline Mat4 Mat4::operator-(float value) const  {
  Mat4 aux;
  aux.m[0]  = m[0]  - value;
  aux.m[1]  = m[1]  - value;
  aux.m[2]  = m[2]  - value;
  aux.m[3]  = m[3]  - value;
  aux.m[4]  = m[4]  - value;
  aux.m[5]  = m[5]  - value;
  aux.m[6]  = m[6]  - value;
  aux.m[7]  = m[7]  - value;
  aux.m[8]  = m[8]  - value;
  aux.m[9]  = m[9]  - value;
  aux.m[10] = m[10] - value;
  aux.m[11] = m[11] - value;
  aux.m[12] = m[12] - value;
  aux.m[13] = m[13] - value;
  aux.m[14] = m[14] - value;
  aux.m[15] = m[15] - value;

  return aux;
}

inline Mat4& Mat4::operator-=(float value) {
  m[0]  -= value;
  m[1]  -= value;
  m[2]  -= value;
  m[3]  -= value;
  m[4]  -= value;
  m[5]  -= value;
  m[6]  -= value;
  m[7]  -= value;
  m[8]  -= value;
  m[9]  -= value;
  m[10] -= value;
  m[11] -= value;
  m[12] -= value;
  m[13] -= value;
  m[14] -= value;
  m[15] -= value;
  return (*this);
}

inline Mat4& Mat4::operator*=(float value) {
  m[0]  *= value;
  m[1]  *= value;
  m[2]  *= value;
  m[3]  *= value;
  m[4]  *= value;
  m[5]  *= value;
  m[6]  *= value;
  m[7]  *= value;
  m[8]  *= value;
  m[9]  *= value;
  m[10] *= value;
  m[11] *= value;
  m[12] *= value;
  m[13] *= value;
  m[14] *= value;
  m[15] *= value;
	return (*this);
}

inline Mat4 Mat4::operator*(float value) const  {
  Mat4 aux;
  aux.m[0]  = m[0]  * value;
  aux.m[1]  = m[1]  * value;
  aux.m[2]  = m[2]  * value;
  aux.m[3]  = m[3]  * value;
  aux.m[4]  = m[4]  * value;
  aux.m[5]  = m[5]  * value;
  aux.m[6]  = m[6]  * value;
  aux.m[7]  = m[7]  * value;
  aux.m[8]  = m[8]  * value;
  aux.m[9]  = m[9]  * value;
  aux.m[10] = m[10] * value;
  aux.m[11] = m[11] * value;
  aux.m[12] = m[12] * value;
  aux.m[13] = m[13] * value;
  aux.m[14] = m[14] * value;
  aux.m[15] = m[15] * value;

  return aux;
}

inline Mat4& Mat4::operator/=(float value) {
  m[0]  /= value;
  m[1]  /= value;
  m[2]  /= value;
  m[3]  /= value;
  m[4]  /= value;
  m[5]  /= value;
  m[6]  /= value;
  m[7]  /= value;
  m[8]  /= value;
  m[9]  /= value;
  m[10] /= value;
  m[11] /= value;
  m[12] /= value;
  m[13] /= value;
  m[14] /= value;
  m[15] /= value;
	return (*this);
}

inline Mat4 Mat4::operator/(float value) const {
	Mat4 aux;
  aux.m[0]  = m[0]  / value;
  aux.m[1]  = m[1]  / value;
  aux.m[2]  = m[2]  / value;
  aux.m[3]  = m[3]  / value;
  aux.m[4]  = m[4]  / value;
  aux.m[5]  = m[5]  / value;
  aux.m[6]  = m[6]  / value;
  aux.m[7]  = m[7]  / value;
  aux.m[8]  = m[8]  / value;
  aux.m[9]  = m[9]  / value;
  aux.m[10] = m[10] / value;
  aux.m[11] = m[11] / value;
  aux.m[12] = m[12] / value;
  aux.m[13] = m[13] / value;
  aux.m[14] = m[14] / value;
  aux.m[15] = m[15] / value;

  return aux;
}

inline bool Mat4::operator==(const Mat4& other) {
  return 
  (m[0]  == other.m[0]) &&
  (m[1]  == other.m[1]) &&
  (m[2]  == other.m[2]) &&
  (m[3]  == other.m[3]) &&
  (m[4]  == other.m[4]) &&
  (m[5]  == other.m[5]) &&
  (m[6]  == other.m[6]) &&
  (m[7]  == other.m[7]) &&
  (m[8]  == other.m[8]) &&
  (m[9]  == other.m[9]) &&
  (m[10] == other.m[10]) &&
  (m[11] == other.m[11]) &&
  (m[12] == other.m[12]) &&
  (m[13] == other.m[13]) &&
  (m[14] == other.m[14]) &&
  (m[15] == other.m[15]);
}

inline bool Mat4::operator!=(const Mat4& other) {
	return 
  (m[0]  != other.m[0]) ||
  (m[1]  != other.m[1]) ||
  (m[2]  != other.m[2]) ||
  (m[3]  != other.m[3]) ||
  (m[4]  != other.m[4]) ||
  (m[5]  != other.m[5]) ||
  (m[6]  != other.m[6]) ||
  (m[7]  != other.m[7]) ||
  (m[8]  != other.m[8]) ||
  (m[9]  != other.m[9]) ||
  (m[10] != other.m[10]) ||
  (m[11] != other.m[11]) ||
  (m[12] != other.m[12]) ||
  (m[13] != other.m[13]) ||
  (m[14] != other.m[14]) ||
  (m[15] != other.m[15]);
}

inline void Mat4::operator=(const Mat4& other) {
  m[0]  = other.m[0];
  m[1]  = other.m[1];
  m[2]  = other.m[2];
  m[3]  = other.m[3];
  m[4]  = other.m[4];
  m[5]  = other.m[5];
  m[6]  = other.m[6];
  m[7]  = other.m[7];
  m[8]  = other.m[8];
  m[9]  = other.m[9];
  m[10] = other.m[10];
  m[11] = other.m[11];
  m[12] = other.m[12];
  m[13] = other.m[13];
  m[14] = other.m[14];
  m[15] = other.m[15];
}

#endif
