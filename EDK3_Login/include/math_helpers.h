#ifndef __MATH_HELPERS_
#define __MATH_HELPERS_ 1

#include "ESAT/math.h"

ESAT::Vec3 Vec3Normalize(ESAT::Vec3 vec);
ESAT::Vec3 Vec3CrossProduct(ESAT::Vec3 u, ESAT::Vec3 v);

float GetTexelValue(unsigned char* data, unsigned int nchannels, unsigned int width, unsigned int height, float x, float y, float max_x, float max_y);

#endif