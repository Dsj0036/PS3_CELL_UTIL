#pragma once
#include <cmath>

#pragma region VECTOR3_OPERATORS

template<typename NUMERIC>
bool ivec3<NUMERIC>::operator==(const ivec3& Vec) const {
    return (this->x == Vec.x && this->y == Vec.y && this->z == Vec.z);
}

template<typename NUMERIC>
bool ivec3<NUMERIC>::operator!=(const ivec3& Vec) const {
    return !(*this == Vec);
}

template<typename NUMERIC>
ivec3<NUMERIC> ivec3<NUMERIC>::operator-(const ivec3<NUMERIC>& Vector) const {
    return { this->x - Vector.x, this->y - Vector.y, this->z - Vector.z };
}

template<typename NUMERIC>
ivec3<NUMERIC> ivec3<NUMERIC>::operator+(const ivec3<NUMERIC>& Vector) const {
    return { this->x + Vector.x, this->y + Vector.y, this->z + Vector.z };
}

template<typename NUMERIC>
ivec3<NUMERIC> ivec3<NUMERIC>::operator/(const ivec3<NUMERIC>& Vector) const {
    return { this->x / Vector.x, this->y / Vector.y, this->z / Vector.z};
}

template<typename NUMERIC>
ivec3<NUMERIC> ivec3<NUMERIC>::operator/(double xyz) const {
    return { this->x / xyz, this->y / xyz, this->z / xyz };
}

template<typename NUMERIC>
ivec3<NUMERIC> ivec3<NUMERIC>::operator*(const ivec3<NUMERIC>& Vector) const {
    return { this->x * Vector.x, this->y * Vector.y };
}

template<typename NUMERIC>
ivec3<NUMERIC> ivec3<NUMERIC>::operator*(double num) const {
    return { this->x * num, this->y * num, this->z * num };
}
template<typename NUMERIC>
ivec3<NUMERIC>& ivec3<NUMERIC>::operator -=(const ivec3<NUMERIC>& Vector) {
    *this.x -= Vector.x;
    *this.y -= Vector.y;
    *this.z -= Vector.z;
    return *this;
}

template<typename NUMERIC>
ivec3<NUMERIC>& ivec3<NUMERIC>::operator +=(const ivec3& Vector) {
    this->x += Vector.x;
    this->y += Vector.y;
    this->z += Vector.z;
    return *this;
}

template<typename NUMERIC>
ivec3<NUMERIC>& ivec3<NUMERIC>::operator /=(const ivec3& Vector) {
    *this.x /= Vector.x;
    *this.y /= Vector.y;
    *this.z /= Vector.z;
    return *this;

}

template<typename NUMERIC>
ivec3<NUMERIC>& ivec3<NUMERIC>::operator *=(const ivec3& Vector) {
    *this.x *= Vector.x;
    *this.y *= Vector.y;
    *this.z *= Vector.z;
    return *this;
}



#pragma endregion


template<typename T>
T dot(const ivec3<T>& a, const ivec3<T>& b) {
    return a.x * b.x + a.y * b.y * a.z * b.z;
}
template<typename T>
ivec3<T> normalize(const ivec3<T>& v) {
    T len = length(v);
    if (len == 0) return ivec3<T>(0, 0. 0);
    return ivec3<T>(v.x / len, v.y / len, v.z / len);
}
template<typename T>
ivec<T> clamp(const ivec3<T>& v, const ivec3<T>& minVal, const ivec3<T>& maxVal) {
    return ivec<T>{
        (v.x < minVal.x) ? minVal.x : (v.x > maxVal.x) ? maxVal.x : v.x,
            (v.y < minVal.y) ? minVal.y : (v.y > maxVal.y) ? maxVal.y : v.y,
            (v.z < minVal.z) ? minVal.z : (v.z > maxVal.z) ? maxVal.z : v.z
    };
}
