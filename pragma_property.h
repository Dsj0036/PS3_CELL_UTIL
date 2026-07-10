#pragma once
#ifndef __SYSTEM_PROPERTIES__ 
#define __SYSTEM_PROPERTIES__ 


#define _PROPERTY2(T, NAME, GETTER, SETTER) _declspec(property(get=GETTER, set=SETTER)) T NAME;

#define _PROPERTY(T, NAME, GETTER)_declspec(property(get=GETTER)) T NAME;
#define _GETTER(T, NAME, BODY) T _get##NAME(){ BODY }
#define _SETTER(T, NAME, BODY) void _set##NAME(const T& value){ BODY }

#define _READONLY_PROPERTY(T, NAME, BODY) _GETTER(T, NAME, BODY)\
_PROPERTY(T, NAME, _get##NAME) 


// Defines an fundamental property that relies on default assignment operators.
#define _PROPERTY_FUNDAMENTAL(T, NAME, VARNAME)  _PROPERTY2(T, NAME, _GETTER(T, NAME, _SETTER(T, NAME, VARNAME = value;))

// Defines an getter that returns the expression defined at BODY
#define _READONLY_PROPERTY_EXPR(T, NAME, BODY) inline _GETTER(T, NAME, return BODY;)\
public: _PROPERTY(T, NAME, _get##NAME) 

#endif