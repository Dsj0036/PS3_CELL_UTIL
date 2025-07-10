template<>
struct HasDefault<ivec<_decimal4>> {
    static inline ivec<_decimal4> get() {
        return ivec<_decimal4>(0, 0);
    }
};
template<>
struct HasDefault<ivec<double>> {
    static inline ivec<double> get() {
        return ivec<double>(0.0, 0.0);
    }
};

template<>
struct HasDefault<ivec3<_decimal4>> {
    static inline ivec3<_decimal4> get() {
        return ivec3<_decimal4>(0, 0, 0);
    }
};


template<>
struct HasDefault<ivec4<_decimal4>> {
    static inline ivec4<_decimal4> get() {
        return ivec4<_decimal4>(0.0f, 0.0f, 0.0f, 0.0f);
    }
};

template<>
struct HasDefault<ivec4<double>> {
    static inline ivec4<double> get() {
        return ivec4<double>(0.0, 0.0, 0.0, 0.0);
    }
};
