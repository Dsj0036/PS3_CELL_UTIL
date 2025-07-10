#pragma once
#pragma once
#include "math.h"
#include "cmath"


typedef struct Vector3D
{
	static Vector3D Empty;

	double x, y, z;
	Vector3D()
	{
		x = y = z = 0;
	}
	Vector3D(double x, double y, double z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	Vector3D operator-(void) const {
		return { -x, -y, -z };
	}
	const bool operator==(const Vector3D& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	const bool operator!=(const Vector3D& v) const {
		return !(*this == v);
	}
	const Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
	const Vector3D& operator-(const Vector3D& v) const {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
	const Vector3D& operator*(double fl) const {
		return Vector3D(x * fl, y * fl, z * fl);
	}
	const Vector3D& operator/(double fl) const {
		return Vector3D(x / fl, y / fl, z / fl);
	}
	const double Length(void) const {
		return (float)sqrtf(x * x + y * y + z * z);
	}
	double getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	const Vector3D Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3D(0, 0, 1);
		flLen = 1 / flLen;
		return Vector3D(x * flLen, y * flLen, z * flLen);
	}

	double Distance(Vector3D const& Vector)
	{
		return std::sqrt(DistanceEx(Vector));
	}
	double DistanceEx(Vector3D const& Vector)
	{
		double _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	double DotProduct(Vector3D const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3D& RoundHalfUp()
	{
		return Vector3D(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	const Vector3D& RoundHalfDown()
	{
		return Vector3D(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	Vector3D cross(const Vector3D& other) const {
		return Vector3D(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	float dot(const Vector3D& other) const {
		return x * other.x + y * other.y + z * other.z;
	}



} Vector3D, Vec3D, * PVector3D, vec3d, Vec3d;

Vector3D Vector3D::Empty{ 0,0,0 };


typedef struct Vector2
{
	static Vector2 Empty;

	float x, y;
	Vector2()
	{
		this->x = this->y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(const Vector2& Vec)
	{
		return (this->x == Vec.x && this->y == Vec.y);
	}

	bool operator!=(const Vector2& Vec)
	{
		return !operator==(Vec);
	}
	Vector2 operator- (const Vector2& Vector)
	{
		return { this->x - Vector.x, this->y - Vector.y };
	}
	Vector2 operator+ (const Vector2& Vector)
	{
		return { this->x + Vector.x, this->y + Vector.y };
	}
	const Vector2 operator/ (Vector2 const& Vector)
	{
		return { this->x / Vector.x, this->y / Vector.y };
	}
	const Vector2 operator/ (float xy)
	{
		return { this->x / xy, this->y / xy };
	}
	const Vector2 operator* (Vector2 const& Vector)
	{
		return { this->x * Vector.x, this->y * Vector.y };
	}

	const Vector2 operator* (double num)
	{
		return { this->x * num, this->y * num };
	}
	Vector2 Clamp(const Vector2& minBounds, const Vector2& maxBounds) const {
		float x = fminf(fmaxf(this->x, minBounds.x), maxBounds.x);
		float y = fminf(fmaxf(this->y, minBounds.y), maxBounds.y);
		return { x, y };
	}
	Vector2 Clamp(const Vector2& bounds)const {
		float x = fminf(this->x, bounds.x);
		float y = fminf(this->y, bounds.y);
		return { x, y };
	}
	Vector2& Clamp2(Vector2 min, Vector2 max) {
		this->x = fminf(fmaxf(this->x, min.x), max.x);
		this->y = fminf(fmaxf(this->y, min.y), max.y);
		return *this;
	}
	Vector2& Clamp2(float minimumX, float minimumY, float maximumX, float maximumY) {
		this->x = fminf(fmaxf(this->x, minimumX), maximumX);
		this->y = fminf(fmaxf(this->y, minimumY), maximumY);
		return *this;
	}

	static Vector2 add(Vector2 left, Vector2 right) {
		return
			left + right;
	}
	static Vector2 substract(Vector2 left, Vector2 right) {
		return
			left - right;
	}
	static Vector2 multiply(Vector2 left, float right) {
		return {
			left.x * right,
			left.y * right,
		};
	}

}Vector2, * PVector2, vec2;



typedef struct Vector2D
{
	static Vector2D Empty;

	double x, y;
	Vector2D()
	{
		this->x = this->y = 0;
	}

	Vector2D(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(const Vector2D& Vec)
	{
		return (this->x == Vec.x && this->y == Vec.y);
	}

	bool operator!=(const Vector2D& Vec)
	{
		return !operator==(Vec);
	}
	const Vector2D operator- (Vector2D const& Vector)
	{
		return { this->x - Vector.x, this->y - Vector.y };
	}
	const Vector2D operator+ (Vector2D const& Vector)
	{
		return { this->x + Vector.x, this->y + Vector.y };
	}
	const Vector2D operator/ (Vector2D const& Vector)
	{
		return { this->x / Vector.x, this->y / Vector.y };
	}
	const Vector2D operator/ (double xy)
	{
		return { this->x / xy, this->y / xy };
	}
	const Vector2D operator* (Vector2D const& Vector)
	{
		return { this->x * Vector.x, this->y * Vector.y };
	}

	const Vector2D operator* (double num)
	{
		return { this->x * num, this->y * num };
	}
	Vector2D Clamp(const Vector2D& minBounds, const Vector2D& maxBounds) const {
		float x = fminf(fmaxf(this->x, minBounds.x), maxBounds.x);
		float y = fminf(fmaxf(this->y, minBounds.y), maxBounds.y);
		return { x, y };
	}
	Vector2D Clamp(const Vector2D& bounds) {
		float x = fminf(this->x, bounds.x);
		float y = fminf(this->y, bounds.y);
		return { x, y };
	}
	void Clamp2(Vector2D min, Vector2D max) {
		this->x = fminf(fmaxf(this->x, min.x), max.x);
		this->y = fminf(fmaxf(this->y, min.y), max.y);
	}
	void Clamp2(double minimumX, double minimumY, double maximumX, double maximumY) {
		this->x = fminf(fmaxf(this->x, minimumX), maximumX);
		this->y = fminf(fmaxf(this->y, minimumY), maximumY);
	}

}Vector2D, * PVector2D, vec2D;

Vector2 Vector2::Empty{ 0,0 };

struct Size : public vec2 {

};

typedef struct Vector3
{
	static Vector3 Empty;

	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	Vector3 operator-(void) const {
		return { -x, -y, -z };
	}
	const bool operator==(const Vector3& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	const bool operator!=(const Vector3& v) const {
		return !(*this == v);
	}
	const Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	const Vector3& operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	const Vector3& operator*(float fl) const {
		return Vector3(x * fl, y * fl, z * fl);
	}
	const Vector3& operator/(float fl) const {
		return Vector3(x / fl, y / fl, z / fl);
	}
	const float Length(void) const {
		return (float)sqrtf(x * x + y * y + z * z);
	}
	const float sqrLen() const {
		return x * x + y * y + z * z;
	}
	float getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	const Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1);
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}
	Vector3& normalized() {
		*this = this->Normalize();
		return *this;
	}
	Vector3 Abs()const {
		return Vector3(ABS(x), ABS(y), ABS(z));
	}
	bool AtLeastOneGreaterThan(float j)const {
		return (x > j || y > j || z > j);
	}
	bool AtLeastOneLessThan(float j)const {
		return (x < j || y < j || z < j);
	}


	float Distance(Vector3 const& Vector)
	{
		return sqrtf(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const& Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3& RoundHalfUp()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	const Vector3& RoundHalfDown()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	Vector3 cross(const Vector3& other) const {
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	float dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	double angleTo2D(const Vector3& target) const {
		double dx = target.x - this->x;
		double dz = target.z - this->z;
		if (isnan(dx) || isnan(dz) || isinf(dx) || isinf(dz))
			return 0.0;
		double angle = atan2(dz, dx) * (180.0 / M_PI);
		if (angle)
			return _dmod(angle + 360.0 + 180.0, 360.0); // align to system via normalize fmod.

	}




} Vector3, * PVector3, vec3;
Vector3 Vector3::Empty{ 0,0,0 };

typedef struct Vector4
{
	static Vector4 Empty;

	float w, x, y, z;
	Vector4()
	{
		w = x = y = z = 0;
	}
	Vector4(float x, float y, float z, float w)
	{
		this->x = x; this->y = y; this->z = z; this->w = w;
	}
	Vector4 operator-(void) const {
		return { -x, -y, -z, -w };
	}
	const bool operator==(const Vector4& v) const {
		return x == v.x && y == v.y && z == v.z && v.w == w;
	}
	const bool operator!=(const Vector4& v) const {
		return !(*this == v);
	}
	const Vector4 operator+(const Vector4& v) const {
		return Vector4(x + v.x, y + v.y, z + v.z, v.w + w);
	}
	const Vector4& operator-(const Vector4& v) const {
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	const Vector4& operator*(float fl) const {
		return Vector4(x * fl, y * fl, z * fl, w * fl);
	}
	const Vector4& operator/(float fl) const {
		return Vector4(x / fl, y / fl, z / fl, w / fl);
	}
	const float Length(void) const {
		return (float)sqrtf(x * x + y * y + z * z + w * w);
	}
	float getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z) + w * w);
	}
	const Vector4 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector4(0, 0, 0, 1);
		flLen = 1 / flLen;
		return Vector4(x * flLen, y * flLen, z * flLen, z * flLen);
	}

	float Distance(Vector4 const& Vector)
	{
		return sqrtf(DistanceEx(Vector));
	}
	float DistanceEx(Vector4 const& Vector)const
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector4 const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector4& RoundHalfUp()
	{
		return Vector4(
			floor(this->x + 0.5),
			floor(this->y + 0.5),
			floor(this->z + 0.5),
			floor(this->w + 0.5)
		);
	}
	const Vector4& RoundHalfDown()
	{
		return Vector4(
			floor(this->x + 0.5),
			floor(this->y + 0.5),
			floor(this->z + 0.5),
			floor(this->w + 0.5)
		);
	}

	float dot(const Vector4& other) const {
		return x * other.x + y * other.y + z * other.z;
	}



} Vector4, * PVector4, vec4;
Vector4 Vector4::Empty{ 0,0,0, 0 };

template<typename T>
struct Vector3T
{
	static Vector3T Empty;

	T x, y, z;
	Vector3T()
	{
		x = y = z = 0;
	}
	Vector3T(T x, T y, T z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	Vector3 operator-(void) const {
		return { -x, -y, -z };
	}
	const bool operator==(const Vector3T& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	const bool operator!=(const Vector3T& v) const {
		return !(*this == v);
	}
	const Vector3T operator+(const Vector3T& v) const {
		return Vector3T(x + v.x, y + v.y, z + v.z);
	}
	const Vector3T& operator-(const Vector3T& v) const {
		return Vector3T(x - v.x, y - v.y, z - v.z);
	}
	const Vector3T& operator*(T fl) const {
		return Vector3T(x * fl, y * fl, z * fl);
	}
	const Vector3T& operator/(T fl) const {
		return Vector3T(x / fl, y / fl, z / fl);
	}
	const float Length(void) const {
		return (float)sqrtf(x * x + y * y + z * z);
	}
	float getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	const Vector3T Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1);
		flLen = 1 / flLen;
		return Vector3T(x * flLen, y * flLen, z * flLen);
	}

	float Distance(Vector3T const& Vector)
	{
		return sqrtf(DistanceEx(Vector));
	}
	float DistanceEx(Vector3T const& Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3T const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3T& RoundHalfUp()
	{
		return Vector3T(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	const Vector3T& RoundHalfDown()
	{
		return Vector3T(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
	Vector3T cross(const Vector3T& other) const {
		return Vector3T(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	float dot(const Vector3T& other) const {
		return x * other.x + y * other.y + z * other.z;
	}



};
typedef Vector3T<int> Vec3i;
typedef Vector3T<int> vec3i;
Vector3T<int> Vector3T<int>::Empty{ 0,0,0 };


typedef Vector3 Vec3;
typedef Vector2 Vec2;

struct VertexUV {
	// u1
	float startX;
	// v1
	float startY;
	// u2
	float endX;
	// v2
	float endY;

	void set(Rectangle rect, vec2 size) {


		float x2, y2;
		x2 = rect.Position.x + rect.Size.x;
		y2 = rect.Position.y + rect.Size.y;


		float u1 = rect.Position.x / size.x;
		float v1 = rect.Position.y / size.y;
		float u2 = x2 / size.x;
		float v2 = y2 / size.y;

		startX = u1;
		startY = v1;
		endX = u2;
		endY = v2;
	}
};
class VertexData
{
	bool w(float f) {
		return f >= 0 && f <= 1;;
	}
	int hexf(float v) {
		return *(int*)&v;
	}
public:

	VertexData() {
		startX = 0;
		startY = 0;
		endX = 0;
		endY = 0;
		Sprite = rect(0, 0, 0, 0);
	}
	static const VertexData Empty;
	VertexData(Vector2 size) :Size(size) {

	}
	VertexData(Rectangle bounds, Vector2 atlasDimensions) {
		Size = atlasDimensions;
		Sprite = bounds;
		Set(bounds);
	}

	VertexData(Rectangle bounds, int atlasDimension) {
		Size = Vector2(atlasDimension, atlasDimension);
		Sprite = bounds;
		Set(bounds);
	}
	// u1
	float startX;
	// v1
	float startY;
	// u2
	float endX;
	// v2
	float endY;
	// Atlas Size 
	Vector2 Size;
	Rectangle Sprite;
	void Set(Rectangle rect) {
		float x2, y2;
		x2 = rect.Position.x + rect.Size.x;
		y2 = rect.Position.y + rect.Size.y;


		float u1 = rect.Position.x / Size.x;
		float v1 = rect.Position.y / Size.y;
		float u2 = x2 / Size.x;
		float v2 = y2 / Size.y;

		startX = u1;
		startY = v1;
		endX = u2;
		endY = v2;
		Sprite = rect;
	}
	// prints this instance to an string pointer (64 bytes)
	void ToString(char* cstr) {


		s_snprintf(cstr, 64, "Vertex (xfloat) UVs: %x|%i|%i|%i",
			hexf(startX),
			hexf(startY),
			hexf(endX),
			hexf(endY));
	}
	float operator[](byte index) {
		switch (index) {
		case 0: return startX;
		case 1: return startY;
		case 2: return endX;
		case 3: return endY;
		default:return -1;
		}
	}

	float u1()const {
		return startX;
	}
	float v1()const {
		return startY;
	}
	float u2()const {
		return endX;
	}
	float v2()const {
		return endY;
	}
	bool valid(byte uv) {
		switch (uv) {
		case 0: return w(startX);
		case 1: return w(startY);
		case 2: return w(endX);
		case 3: return w(endY);
		default:return false;
		}
	}
	bool isInvalid() {
		return
			w(startX) &&
			w(startY) &&
			w(endX) &&
			w(endY);
	}
	bool isEmpty() const {
		return startX == 0 &&
			startY == 0 &&
			endX == 0 &&
			endY == 0;
	}
	static VertexData New(Vector2 origin, Vector2 size, Vector2 baseDimensions) {
		return { { origin, size }, baseDimensions };
	};
	static VertexData New(float x, float y, float sx, float sy, float asx, float asy) {
		return { { {x,y}, {sx,sy}}, {asx,asy} };

	}
};

const VertexData VertexData::Empty{};
Vec3* getLookAtVec(float pitch, float yaw) {
	return new Vector3(
		fabs(sinf(degToRad(pitch - 90.0f))) * sinf(degToRad(yaw - 180.0f)),
		sinf(degToRad(pitch - 180.0f)),
		fabs(sinf(degToRad(pitch - 90.0f))) * cosf(degToRad(yaw))
	);
}


namespace mth {
	double dot(const vec3& a, const vec3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	double cross(const vec3& a, const vec3& b) {
		return a.x * b.y - a.y * b.x;
	}
	Rectangle rect(float x, float y, float width, float height) {
		return { {x,y}, { width, height } };
	}

}

void ClampScreenPosition(Vec2& screenPos, float screenWidth, float screenHeight) {
	// Clampa la posición para asegurarse de que el ícono se mantenga dentro de los límites de la pantalla

	screenPos.x = std::fmax(0.0f, std::fmin(screenPos.x, screenWidth));
	screenPos.y = std::fmax(0.0f, std::fmin(screenPos.y, screenHeight));
}

