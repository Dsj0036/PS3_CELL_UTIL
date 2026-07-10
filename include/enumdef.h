#pragma once
#define SMART_ENUM(name, ...) \
class e##name final { \
public: \
    enum Enum { __VA_ARGS__ }; \
}; \
using name = e##name::Enum;






