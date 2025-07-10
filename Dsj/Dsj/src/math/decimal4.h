#pragma once

typedef struct _decimal4 {
protected:
    union _val {
        float _flt;
        int _int;
        short _shrt;

        void setvalue(float value);
        void setvalue(int value);
        void setvalue(short value);

        float getvalue() const;
        float getfloat() const;
        int getint() const;
        short getshort() const;

        operator float() const;
        explicit operator int() const;
        explicit operator short() const;
    } d;

public:
    _decimal4();
    _decimal4(float f);
    _decimal4(int i);
    _decimal4(short s);
    _decimal4(const _decimal4& other);

    operator float() const;

    _decimal4& operator=(const _decimal4& other);
    _decimal4& operator=(float f);
    _decimal4& operator=(int i);
    _decimal4& operator=(short s);

    _decimal4& operator -= (const _decimal4 & other);
    _decimal4& operator += (const _decimal4 & other);
    _decimal4& operator /= (const _decimal4 & other);
    _decimal4& operator *= (const _decimal4 & other);

    // 
    // bool operator<(const _decimal4& other) const;
    // bool operator>(const _decimal4& other) const;
    // bool operator<=(const _decimal4& other) const;
    // bool operator>=(const _decimal4& other) const;

    bool operator==(const _decimal4& other) const;
    bool operator!=(const _decimal4& other) const;

    float& _float();
    const float& _float() const;

    inline bool equals(const _decimal4& other)const { return this->d.getfloat() == other.d.getfloat(); }
    
    static _decimal4 floor(const _decimal4&);
    static _decimal4 mod(const _decimal4&, const _decimal4&);
    static _decimal4 sqrt(const _decimal4&);
    static _decimal4 clamp(const _decimal4&, const _decimal4&, const _decimal4&);
} Decimal, numeric_t;
