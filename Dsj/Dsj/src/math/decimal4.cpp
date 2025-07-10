#include "decimal4.h"
#include <math.h>
// Métodos de _val
void _decimal4::_val::setvalue(float value) {
    _flt = value;
}
void _decimal4::_val::setvalue(int value) {
    _flt = static_cast<float>(value);
}
void _decimal4::_val::setvalue(short value) {
    _flt = static_cast<float>(value);
}
float _decimal4::_val::getvalue() const {
    return _flt;
}
float _decimal4::_val::getfloat() const {
    return _flt;
}
int _decimal4::_val::getint() const {
    return static_cast<int>(_flt);
}
short _decimal4::_val::getshort() const {
    return static_cast<short>(_flt);
}

_decimal4::_val::operator float() const {
    return getfloat();
}
_decimal4::_val::operator int() const {
    return getint();
}
_decimal4::_val::operator short() const {
    return getshort();
}

_decimal4::_decimal4() {
    d.setvalue(0.0f);
}
_decimal4::_decimal4(float f) {
    d.setvalue(f);
}
_decimal4::_decimal4(int i) {
    d.setvalue(i);
}
_decimal4::_decimal4(short s) {
    d.setvalue(s);
}
_decimal4::_decimal4(const _decimal4& other) {
    d.setvalue(other.d.getfloat());
}

 _decimal4::operator float() const{
    return d.getfloat();
}

_decimal4& _decimal4::operator=(const _decimal4& other) {
    d.setvalue(other.d.getfloat());
    return *this;
}
_decimal4& _decimal4::operator=(float f) {
    d.setvalue(f);
    return *this;
}
_decimal4& _decimal4::operator=(int i) {
    d.setvalue(i);
    return *this;
}
_decimal4& _decimal4::operator=(short s) {
    d.setvalue(s);
    return *this;
}

_decimal4& _decimal4::operator -= (const _decimal4& other) {
    this->d._flt -= other.d._flt;
    return *this;
};
_decimal4& _decimal4::operator += (const _decimal4& other) {
    this->d._flt += other.d._flt;
    return *this;
};
_decimal4& _decimal4::operator /= (const _decimal4& other) {
    this->d._flt /= other.d._flt;
    return *this;
};
_decimal4& _decimal4::operator *= (const _decimal4& other) {
    this->d._flt *= other.d._flt;
    return *this;
};

#if FALSE
bool _decimal4::operator<(const _decimal4& other) const{return this->_float() < other._float();}
bool _decimal4::operator>(const _decimal4& other) const{return this->_float() > other._float();}
bool _decimal4::operator<=(const _decimal4& other) const{return this->_float() <= other._float();}
bool _decimal4::operator>=(const _decimal4& other) const{return this->_float() >= other._float();}
#endif
bool _decimal4::operator==(const _decimal4& other) const{ return this->_float() == other._float(); }
bool _decimal4::operator!=(const _decimal4& other) const { return !(*this == other); }


/*As float */
float& _decimal4::_float() {
    return this->d._flt;

}
const float& _decimal4::_float() const {
    return this->d._flt;
}

_decimal4 _decimal4::floor(const _decimal4& other) {
    return std::floorf(other);
} 
_decimal4 _decimal4::mod(const _decimal4& left, const _decimal4& right) {
    return std::fmodf(left, right);
}
_decimal4 _decimal4::sqrt(const _decimal4& other) {
    return std::sqrtf(other);

}
_decimal4 _decimal4::clamp(const _decimal4& val, const _decimal4& min, const _decimal4& max) {
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}
