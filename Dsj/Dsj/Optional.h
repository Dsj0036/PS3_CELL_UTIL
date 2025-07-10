#ifndef OPTIONAL_H
#define OPTIONAL_H

#include "System.h" // Para placement new
#include <new>

template <typename T>
class Optional {
private:
    bool has_value;
    char storage[sizeof(T)]; // Almacenamiento sin construir

    T* ptr() { return reinterpret_cast<T*>(storage); }
    const T* ptr() const { return reinterpret_cast<const T*>(storage); }

public:
    Optional() : has_value(false) {}

    Optional(const T& value) : has_value(true) {
        new (storage) T(value); // Construcción en almacenamiento
    }

    Optional(const Optional& other) : has_value(other.has_value) {
        if (has_value) new (storage) T(*other.ptr());
    }

    Optional& operator=(const Optional& other) {
        if (this != &other) {
            reset();
            if (other.has_value) {
                new (storage) T(*other.ptr());
                has_value = true;
            }
        }
        return *this;
    }

    ~Optional() { reset(); }

    void reset() {
        if (has_value) {
            ptr()->~T();
            has_value = false;
        }
    }

    void emplace(const T& value) {
        reset();
        new (storage) T(value);
        has_value = true;
    }

    bool hasValue() const { return has_value; }

    T& value() {
        if (!has_value) Throw(System::InvalidOperationException(0, "Bad Optional Access"));
        return *ptr();
    }


    const T& value() const {
        if (!has_value) Throw(System::InvalidOperationException(0, "Bad Optional Access"));
        return *ptr();
    }
};

#endif // OPTIONAL_H
