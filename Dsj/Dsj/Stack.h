#pragma once

#include "System.h"
#include "include\collections\array.h"
template<typename T> 
class Stack {
private:
	System::Array<T> Elements;
public:
	Stack() {

	}
	T& operator[](const size_t& index) {
		return Elements[index];
	}


	T* const Push(const T& element = {}) {
		return Elements.Add(element);
	}
	void Pop() {
		if (Elements.Count() > 0) {
			Elements.RemoveAt(Elements.Count() - 1);
		}
	}
	int32_t Count() const {
		return Elements.Count();
	}
	T& ElementAt(signed int r) {
		if (r >= 0)
			return Elements[r];
		else
			return Elements[Elements.Count() - 1 + r];
	}
	T* const PointAt(size_t r){
		return &Elements[r];
	}
	T& Last() {
		return ElementAt(Count() - 1);
	}
	T& LastOr(T& q) {
		return Count() > 0 ? Last() : q;
	}
	T& First() {
		return ElementAt(0);
	}
	Stack<T> & operator --() {
		Pop();
		return *this;
	}
	Stack<T>& operator ++() {
		Push({});
		return *this;
	}
};