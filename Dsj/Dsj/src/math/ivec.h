#pragma once
#include "decimal4.h"
#include "..\default_traits.h"

template<typename NUMERIC = _decimal4>
struct ivec {

	ivec() : x(0), y(0) {}
	ivec(NUMERIC x_, NUMERIC y_) : x(x_), y(y_) {}

	NUMERIC x;
	NUMERIC y;


	// Comparación
	bool operator==(const ivec& Vec) const;
	bool operator!=(const ivec& Vec) const;

	ivec operator-(const ivec& Vector) const;
	ivec operator+(const ivec& Vector) const;
	ivec operator/(const ivec& Vector) const;
	ivec operator/(double xy) const;
	ivec operator*(const ivec& Vector) const;
	ivec operator*(double num) const;

	ivec& operator -=(const ivec& Vector);
	ivec& operator +=(const ivec& Vector);
	ivec& operator /=(const ivec& Vector);
	ivec& operator *=(const ivec& Vector);
	


	static const ivec empty;
};
template<typename NUMERIC = _decimal4>
struct ivec3 : ivec<NUMERIC> {
	ivec3() : ivec<NUMERIC>(), z(0) {}
	ivec3(NUMERIC x_, NUMERIC y_, NUMERIC z_) : ivec<NUMERIC>(x_, y_), z(z_) {}

	NUMERIC z;


	bool operator==(const ivec3& Vec) const;
	bool operator!=(const ivec3& Vec) const;

	ivec3 operator-(const ivec3& Vector) const;
	ivec3 operator+(const ivec3& Vector) const;
	ivec3 operator/(const ivec3& Vector) const;
	ivec3 operator/(double xy) const;
	ivec3 operator*(const ivec3& Vector) const;
	ivec3 operator*(double num) const;

	ivec3& operator -=(const ivec3& Vector);
	ivec3& operator +=(const ivec3& Vector);
	ivec3& operator /=(const ivec3& Vector);
	ivec3& operator *=(const ivec3& Vector);

	static const ivec3 empty;
};
template<typename NUMERIC = _decimal4>
struct ivec4 : ivec3<NUMERIC>{
	NUMERIC w;

	ivec4() : ivec3<NUMERIC>(), w(0) {}
	ivec4(NUMERIC x_, NUMERIC y_, NUMERIC z_, NUMERIC w_) : ivec3<NUMERIC>(x_, y_, z_), w(w_) {}


	bool operator==(const ivec4& Vec) const;
	bool operator!=(const ivec4& Vec) const;

	ivec4 operator-(const ivec4& Vector) const;
	ivec4 operator+(const ivec4& Vector) const;
	ivec4 operator/(const ivec4& Vector) const;
	ivec4 operator/(double xy) const;
	ivec4 operator*(const ivec4& Vector) const;
	ivec4 operator*(double num) const;

	ivec4& operator -=(const ivec4& Vector);
	ivec4& operator +=(const ivec4& Vector);
	ivec4& operator /=(const ivec4& Vector);
	ivec4& operator *=(const ivec4& Vector);

	static const ivec4 empty;
};

typedef ivec<_decimal4> vec2f, Vector2;

typedef ivec<double> vec2d, Vector2d;

typedef ivec3<_decimal4> vec3f, Vector3;
typedef ivec3<double> vec3d, Vector3d;

typedef ivec4<_decimal4> vec4f, Vector4;
typedef ivec4<double> vec4d, Vector4d;


template<> struct HasDefault<ivec<_decimal4>>;
template<> struct HasDefault<ivec<double>>;

template<> struct HasDefault<ivec3<_decimal4>>;
template<> struct HasDefault<ivec3<double>>;

template<> struct HasDefault<ivec4<_decimal4>>;
template<> struct HasDefault<ivec4<double>>;

template<typename T>
T dot(const ivec<T>& a, const ivec<T>& b);
template<typename T>
T length(const ivec<T>& v);
template<typename T>
ivec<T> normalize(const ivec<T>& v);
template<typename T>
ivec<T> clamp(const ivec<T>& v, const ivec<T>& minVal, const ivec<T>& maxVal);

#ifndef IVEC
#define IVEC
#include "ivec.inl"
#include "ivec3.inl"
#include "ivec4.inl"
#include "ivec_default_vals.inl"
#endif



