#pragma once
#ifndef _STL_COMPILER_PREPROCESSOR
#define _STL_COMPILER_PREPROCESSOR

#include <memory>
#include <initializer_list>
#include "ns.h"
_SYS_NS

template<typename T, typename Allocator = std::allocator<T>>
class vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    Allocator allocator_;

public:
    vector();
    vector(size_t c);
    vector(const vector& other);
    vector(const vector<T>& other, int32_t startOffset, int32_t count);
    vector(const std::initializer_list<T>& right);
    ~vector();

    vector<T>& operator=(const vector<T>& other);

    T* data() const;
    int contains(const T& r) const;
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T* push_back(const T& value);
    void insert(size_t index, const T& value);

    int f_extend_zeroed(int length);
    T* back();
    int f_construct_at(int i, T&& value);
    int f_inject_at(int i, const T* data, int count);
    T* add();

    void push_range(const T(value)[]);
    void push_range(const T* R, size_t length);

    void pop_back();
    void f_fixed(size_t size);
    size_t used_size() const;
    void reserve(size_t new_capacity);
    void clear();

    T* begin();
    int remove_at(size_t index);
    int remove(T& index);
    void reverse();
    T* end();

    const T* begin() const;
    const T* end() const;

    static vector va(int count, ...);
    T* erase(T* pos);
    T* erase(T* first, T* last);

    T& emplace_back(const T& object);

    template<typename... VA>
    T& emplace_back_va(VA&&... argument_list);

    T& moved_emplace_back(T&& object);

    static inline vector<T> And(const vector<T>& left, const std::initializer_list<T>& right);
    vector<T>& And(const vector<T>& right);

    template<typename... Args>
    void emplace(size_t index, Args&&... args);

    bool disjoint(const vector<T>& other) const;

private:
    void ensure_capacity(size_t min_capacity);
    void reallocate(size_t new_capacity);
};

_SYS_ENS

#include "vector.inl"

#endif
