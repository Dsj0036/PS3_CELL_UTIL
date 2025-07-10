#pragma once
#include <cmath>

#pragma region VECTOR2_OPERATORS

template<typename NUMERIC>
bool ivec<NUMERIC>::operator==(const ivec& Vec) const {
    return (this->x == Vec.x && this->y == Vec.y);
}

template<typename NUMERIC>
bool ivec<NUMERIC>::operator!=(const ivec& Vec) const {
    return !(*this == Vec);
}

template<typename NUMERIC>
ivec<NUMERIC> ivec<NUMERIC>::operator-(const ivec<NUMERIC>& Vector) const {
    return { this->x - Vector.x, this->y - Vector.y };
}

template<typename NUMERIC>
ivec<NUMERIC> ivec<NUMERIC>::operator+(const ivec<NUMERIC>& Vector) const {
    return { this->x + Vector.x, this->y + Vector.y };
}

template<typename NUMERIC>
ivec<NUMERIC> ivec<NUMERIC>::operator/(const ivec<NUMERIC>& Vector) const {
    return { this->x / Vector.x, this->y / Vector.y };
}

template<typename NUMERIC>
ivec<NUMERIC> ivec<NUMERIC>::operator/(double xy) const {
    return { this->x / xy, this->y / xy };
}

template<typename NUMERIC>
ivec<NUMERIC> ivec<NUMERIC>::operator*(const ivec<NUMERIC>& Vector) const {
    return { this->x * Vector.x, this->y * Vector.y };
}

template<typename NUMERIC>
ivec<NUMERIC> ivec<NUMERIC>::operator*(double num) const {
    return { this->x * num, this->y * num };
}
template<typename NUMERIC>
ivec<NUMERIC>& ivec<NUMERIC>::operator -=(const ivec<NUMERIC>& Vector) {
    *this.x -= Vector.x;
    *this.y -= Vector.y;
    return *this;
}

template<typename NUMERIC>
ivec<NUMERIC>& ivec<NUMERIC>::operator +=(const ivec& Vector) {
    this->x += Vector.x;
    this->y += Vector.y;
    return *this;
}

template<typename NUMERIC>
ivec<NUMERIC>& ivec<NUMERIC>::operator /=(const ivec& Vector) {
    *this.x /= Vector.x;
    *this.y /= Vector.y;
    return *this;

}

template<typename NUMERIC>
ivec<NUMERIC>& ivec<NUMERIC>::operator *=(const ivec& Vector) {
    *this.x *= Vector.x;
    *this.y *= Vector.y;
    return *this;
}



#pragma endregion


template<typename T>
T dot(const ivec<T>& a, const ivec<T>& b) {
    return a.x * b.x + a.y * b.y;
}
template<typename T>
T length(const ivec<T>& v) {
    return std::sqrt(dot(v, v));
}

template<typename T>
ivec<T> normalize(const ivec<T>& v) {
    T len = length(v);
    if (len == 0) return ivec<T>(0, 0);
    return ivec<T>(v.x / len, v.y / len);
}
template<typename T>
ivec<T> clamp(const ivec<T>& v, const ivec<T>& minVal, const ivec<T>& maxVal) {
    return ivec<T>{
        (v.x < minVal.x) ? minVal.x : (v.x > maxVal.x) ? maxVal.x : v.x,
            (v.y < minVal.y) ? minVal.y : (v.y > maxVal.y) ? maxVal.y : v.y
    };
}
