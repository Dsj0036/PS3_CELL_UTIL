#include "default_traits.h"
template<typename T> T HasDefault<T>::get() {return T();}

int HasDefault<int>::get() {return 0;}
double HasDefault<double>::get() {return 0.0;}
float HasDefault<float>::get() {return 0.0f;}
short HasDefault<short>::get() {return 0;}
char HasDefault<char>::get() {return '\0';}
unsigned char HasDefault<unsigned char>::get() {return 0;}
unsigned long HasDefault<unsigned long>::get() { return 0UL; }
