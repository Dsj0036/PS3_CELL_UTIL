#pragma once
#include "math.h"
#include "cmath"
#if false
typedef struct Vector2
{
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

	bool operator==(Vector2& Vec)
	{
		return (this->x == Vec.x && this->y == Vec.y);
	}
	const Vector2& operator- (Vector2 const& Vector)
	{
		return Vector2(this->x - Vector.x, this->y - Vector.y);
	}
	const Vector2& operator+ (Vector2 const& Vector)
	{
		return Vector2(this->x + Vector.x, this->y + Vector.y);
	}
}Vector2, * PVector2;

typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const Vector3& operator-(void) const {
		return Vector3(-x, -y, -z);
	}
	const bool operator==(const Vector3& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	const bool operator!=(const Vector3& v) const {
		return !(*this == v);
	}
	const Vector3& operator+(const Vector3& v) const {
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
	float Vector3::getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	const Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
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



} Vector3, * PVector3;


typedef struct Rectangle {
public:
	Rectangle(Vector2 pos, Vector2 size) :Position(pos), Size(size) {

	}
	Rectangle() {

	}
	Vector2 Position;
	Vector2 Size;

	Rectangle NextCenter() {
		return Rectangle({ Position.x + (Size.x / 2), Position.y }, Size);
	}
	Rectangle Scale(float rate) {

		return Rectangle({ Position.x, Position.y }, { Size.x * rate, Size.y * rate });
	}
	Rectangle operator/(float last_center) {
		return Rectangle({ Position.x - (Size.x / last_center), Position.y }, Size);
	}
	Rectangle operator*(float rescale) {
		return Scale(rescale);
	}
	Rectangle incX(float x) {
		return Rectangle({ Position.x + x, Position.y }, Size);
	}
	Rectangle incY(float y) {
		return Rectangle({ Position.x, Position.y + y }, Size);
	}
	Rectangle incWidth(float x) {
		return Rectangle({ Position.x, Position.y }, { Size.x + x, Size.y });
	}
	Rectangle incHeight(float y) {
		return Rectangle({ Position.x, Position.y }, { Size.x , Size.y + y });
	}

};

Rectangle rect(float x, float y, float width, float height) {
	return { {x,y}, { width, height } };
}


namespace Math {
#define PI (3.1415926535897931)
	float abs(float a) {
		if (a < 0)
			return a * -1;
		return a;
	}
	float DegreesToRadians(float Degrees)
	{
		return Degrees * PI / 180.0f;
	}
	double Two(double d) {
		return d * d;
	}
	float RadiansToDegrees(float Radians)
	{
		return Radians * 180.0f / PI;
	}


	float sin(float deg) {
		deg = fmodf(deg + 360.0f, 360.0f); // Normalizar el ángulo
		if (deg > 180) {
			deg -= 360; // Convertir a rango [-180, 180]
		}

		// Aproximación (puedes reemplazarla por una más precisa)
		float ret = (float)(4 * deg * (180 - deg)) / (40500 - (deg * (180 - deg)));
		return ret; // Esto podría dar resultados no precisos, considerar una mejor aproximación
	}


	float cos(float AnglesDeg) {
		return sin(AnglesDeg + 90.0f); // Usar la relación entre seno y coseno
	}
	// Implementación de la función asin(x) utilizando la serie de Taylor
	float asin(float x) {
		if (x < -1.0f || x > 1.0f) {
			// Fuera del dominio de asin(x)
			return NAN;
		}

		float result = x;
		float term = x;
		float x_squared = x * x;

		// Serie de Taylor para asin(x)
		for (int n = 1; n <= 10; ++n) {
			term *= x_squared * (2 * n - 1) / (2 * n);
			result += term / (2 * n + 1);
		}

		return result;
	}

	// Implementación de la función acos(x) basada en la identidad acos(x) = pi/2 - asin(x)
	float acos(float x) {
		if (x < -1.0f || x > 1.0f) {
			// Fuera del dominio de acos(x)
			return NAN;
		}

		return PI / 2 - asin(x);
	}


	double atan(double x, int n)
	{
		double a = 0.0;// 1st term
		double sum = 0.0;

		// special cases
		if (x == 1.0) return PI / 4.0;
		if (x == -1.0) return -PI / 4.0;

		if (n > 0)
		{
			if ((x < -1.0) || (x > 1.0))
			{
				// constant term
				if (x > 1.0)
					sum = PI / 2.0;
				else
					sum = -PI / 2.0;
				// initial value of a
				a = -1.0 / x;
				for (int j = 1; j <= n; j++)
				{
					sum += a;
					a *= -1.0 * (2.0 * j - 1) / ((2.0 * j + 1) * x * x);// next term from last
				}
			}
			else// -1 < x < 1
			{
				// constant term
				sum = 0.0;
				// initial value of a
				a = x;
				for (int j = 1; j <= n; j++)
				{
					sum += a;
					a *= -1.0 * (2.0 * j - 1) * x * x / (2.0 * j + 1);// next term from last
				}
			}
			//r_err = a;// max. error = 1st term not taken for alternating series
		}

		return sum;
	}

	float tan(float x) {
		float sinVal = Math::sin(x);
		float cosVal = Math::cos(x);

		// Manejo de división por cero
		if (cosVal == 0) {
			return (sinVal > 0) ? INFINITY : -INFINITY; // Retornar infinito positivo o negativo
		}

		return sinVal / cosVal;
	}
	double atan2(double y, double x)
	{
		double u = atan(y / x, 24);
		if (x < 0.0)// 2nd, 3rd quadrant
		{
			if (u > 0.0)// will go to 3rd quadrant
				u -= PI;
			else
				u += PI;
		}
		return u;
	}
}
bool IsEmpty(Vector3& point) {
	return point.x == 0 && point.y == 0 && point.z == 0;
}
Vector3 calculateDirectionVector(float yaw, float pitch) {
	float yawRad = yaw * (PI / 180.0f);
	float pitchRad = pitch * (PI / 180.0f);

	Vector3 direction;
	direction.x = Math::cos(pitchRad) * Math::cos(yawRad);
	direction.y = Math::sin(pitchRad);
	direction.z = Math::cos(pitchRad) * Math::sin(yawRad);

	return direction;
}

float calculateAngle(Vector3 from, Vector3 to) {
	float dotProduct = from.x * to.x + from.z * to.z;


	float magnitudeFrom = s_iterative_sqrt(from.x * from.x + from.z * from.z);
	float magnitudeTo = s_iterative_sqrt(to.x * to.x + to.z * to.z);

	float angleRad = Math::acos(dotProduct / (magnitudeFrom * magnitudeTo));
	return Math::RadiansToDegrees(angleRad);
}

Vector2 getCircunferencialIndicatorPosition(float screenWidth, float screenHeight, float radius, float angle) {
	Vector2 center = { screenWidth / 2, screenHeight / 2 };
	Vector2 indicator;

	indicator.x = center.x + radius * Math::cos(angle * (PI / 180.0f));
	indicator.y = center.y + radius * Math::sin(angle * (PI / 180.0f));

	return indicator;
}

Vector2 getCircunferencialRadarIndicator(float screenWidth, float screenHeight, float radius, float yaw, float pitch, Vector3 playerPosition, Vector3 targetPosition) {
	// Calcular la dirección del jugador
	Vector3 playerDirection = calculateDirectionVector(yaw, pitch);

	// Calcular el vector desde el jugador hacia el objetivo
	Vector3 toTarget = {
		targetPosition.x - playerPosition.x,
		targetPosition.y - playerPosition.y,
		targetPosition.z - playerPosition.z
	};

	// Calcular el ángulo entre la dirección del jugador y el vector hacia el objetivo
	float angle = calculateAngle(playerDirection, toTarget);

	// Determinar si el objetivo está a la izquierda o derecha
	if ((playerDirection.x * toTarget.z - playerDirection.z * toTarget.x) < 0) {
		angle = -angle;
	}

	// Calcular la posición del indicador en la pantalla
	Vector2 indicatorPosition = getCircunferencialIndicatorPosition(screenWidth, screenHeight, radius, angle);

	return indicatorPosition;
}

#define SHOULD_USE_STD_MATH false
#if SHOULD_USE_STD_MATH
#define TAN tanf
#define COS cosf
#define SIN sinf
#define ABSO abs
#else 
#define TAN Math::tan
#define COS Math::cos
#define SIN Math::sin
#define ABSO Math::abs
#endif





float degToRad(float degrees) {
	return degrees * (M_PI / 180.0f);
}

typedef Vector3 Vec3;
typedef Vector2 Vec2;

Vec3* getLookAtVec(float pitch, float yaw) {
	return new Vector3(
		fabs(sinf(degToRad(pitch - 90.0f))) * sinf(degToRad(yaw - 180.0f)),
		sinf(degToRad(pitch - 180.0f)),
		fabs(sinf(degToRad(pitch - 90.0f))) * cosf(degToRad(yaw))
	);
}



void ClampScreenPosition(Vec2& screenPos, float screenWidth, float screenHeight) {
	// Clampa la posición para asegurarse de que el ícono se mantenga dentro de los límites de la pantalla

	screenPos.x = std::fmax(0.0f, std::fmin(screenPos.x, screenWidth));
	screenPos.y = std::fmax(0.0f, std::fmin(screenPos.y, screenHeight));
}





class VertexData
{
	bool w(float f) {
		return f >= 0 && f <= 1;;
	}
	int hexf(float v) {
		return *(int*)&v;
	}
public:

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
		case 0: return startX; break;
		case 1: return startY; break;
		case 2: return endX; break;
		case 3: return endY; break;
		default:return -1; break;;
		}
	}

	bool valid(byte uv) {
		switch (uv) {
		case 0: return w(startX); break;
		case 1: return w(startY); break;
		case 2: return w(endX); break;
		case 3: return w(endY); break;
		default:return false; break;
		}
	}
	bool isInvalid() {
		return
			w(startX) &&
			w(startY) &&
			w(endX) &&
			w(endY);
	}
};
#endif