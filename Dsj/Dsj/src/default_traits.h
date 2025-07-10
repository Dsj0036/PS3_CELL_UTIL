#pragma once
template<typename T>
struct HasDefault {
	static_assert(sizeof(T) == 0, "HasDefault<T>::get() Is not specialized for this type.");
	static inline T get();
	T operator()() {return get();}
	T operator()() const{return get();}
};
template<typename T> using _defaultable = HasDefault<T>;
template<typename T> using _default_t = HasDefault<T>;

template<> struct HasDefault<int> {static int get();};
template<> struct HasDefault<double> { static double get(); };
template<> struct HasDefault<float> { static float get(); };
template<> struct HasDefault<short> { static short get(); };
template<> struct HasDefault<char> { static char get(); };
template<> struct HasDefault<unsigned char> { static unsigned char get(); };
template<> struct HasDefault<unsigned long> { static unsigned long get(); };

template<typename T>
inline T default_value() {
	return HasDefault<T>::get();
}