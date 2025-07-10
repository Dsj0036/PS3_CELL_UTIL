#pragma once
#include <cmath>

#pragma region VECTOR3_OPERATORS

template<typename NUMERIC>
bool ivec4<NUMERIC>::operator==(const ivec4& Vec) const {
    return (this->x == Vec.x && this->y == Vec.y && this->z == Vec.z && this->w == Vec.w);
}

template<typename NUMERIC>
bool ivec4<NUMERIC>::operator!=(const ivec4& Vec) const {
    return !(*this == Vec);
}

template<typename NUMERIC>
ivec4<NUMERIC> ivec4<NUMERIC>::operator-(const ivec4<NUMERIC>& Vector) const {
    return { this->x - Vector.x, this->y - Vector.y, this->z - Vector.z, this->w - Vector.w };
}

template<typename NUMERIC>
ivec4<NUMERIC> ivec4<NUMERIC>::operator+(const ivec4<NUMERIC>& Vector) const {
    return { this->x + Vector.x, this->y + Vector.y, this->z + Vector.z, this->w + Vector.z };
}

template<typename NUMERIC>
ivec4<NUMERIC> ivec4<NUMERIC>::operator/(const ivec4<NUMERIC>& Vector) const {
    return { this->x / Vector.x, this->y / Vector.y, this->z / Vector.z, this->w /Vector.z };
}

template<typename NUMERIC>
ivec4<NUMERIC> ivec4<NUMERIC>::operator/(double xyz) const {
    return { this->x / xyz, this->y / xyz, this->z / xyz, this->w / xyz };
}

template<typename NUMERIC>
ivec4<NUMERIC> ivec4<NUMERIC>::operator*(const ivec4<NUMERIC>& Vector) const {
    return { this->x * Vector.x, this->y * Vector.y, this->w * Vector.w };
}

template<typename NUMERIC>
ivec4<NUMERIC> ivec4<NUMERIC>::operator*(double num) const {
    return { this->x * num, this->y * num, this->z * num, this->w * num };
}
template<typename NUMERIC>
ivec4<NUMERIC>& ivec4<NUMERIC>::operator -=(const ivec4<NUMERIC>& Vector) {
    *this.x -= Vector.x;
    *this.y -= Vector.y;
    *this.z -= Vector.z;
    *this.w -= Vector.w;
    return *this;
}

template<typename NUMERIC>
ivec4<NUMERIC>& ivec4<NUMERIC>::operator +=(const ivec4& Vector) {
    this->x += Vector.x;
    this->y += Vector.y;
    this->z += Vector.z;
    this->w += Vector.w;
    return *this;
}

template<typename NUMERIC>
ivec4<NUMERIC>& ivec4<NUMERIC>::operator /=(const ivec4& Vector) {
    *this.x /= Vector.x;
    *this.y /= Vector.y;
    *this.z /= Vector.z;
    *this.w /= Vector.w;
    return *this;

}

template<typename NUMERIC>
ivec4<NUMERIC>& ivec4<NUMERIC>::operator *=(const ivec4& Vector) {
    *this.x *= Vector.x;
    *this.y *= Vector.y;
    *this.z *= Vector.z;
    *this.w *= Vector.w;
    return *this;
}



#pragma endregion

