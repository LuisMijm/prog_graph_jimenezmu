
#include "math_library/matrix_4.h"

Mat4::Mat4() {
	for (int i = 0; i < 16; ++i) {
		m[i] = 0.0f;
	}
}

Mat4::Mat4(float array[16]) {
	for (int i = 0; i < 16; ++i) {
		m[i] = array[i];
	}
}

Mat4::Mat4(float value) {
	for (int i = 0; i < 16; ++i) {
		m[i] = value;
	}
}

Mat4::Mat4(const Mat4& copy) {
	for (int i = 0; i < 16; ++i) {
		m[i] = copy.m[i];
	}
}

Mat4::Mat4(const float a[16]) {
	for (int i = 0; i < 16; ++i) {
		m[i] = a[i];
	}
}

Mat4::~Mat4() {
}
