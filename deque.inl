#include "memory.h"
#include "_ns.h"
_SYS_NS

template<typename T>
deque<T>::deque(int capacity) : _head(0), _tail(0), _size(0), _capacity(0) {
	_sys_assertd(capacity >= 0, "Initial capacity must be non-negative");
	_array = nullptr;
	grow(capacity);
}

template<typename T>
bool deque<T>::compare_objects(T& left, T& right) const {
	return left == right || &left == &right;
}

template<typename T>
bool deque<T>::compare_objects(const T& left, const T& right) const {
	return left == right || &left == &right;
}

template<typename T>
bool deque<T>::compare_objects(const T& left, T& right) const {
	return left == right || &left == &right;
}
template<typename T>
deque<T>::deque() : deque(0) {}

template<typename T>
deque<T>::deque(const deque<T>& other) : deque(other._size) {
	_sys_assertd(this != &other, "Self-copy not allowed");
	other._do_clone(this);
}

template<typename T>
bool deque<T>::empty() const { return _size == 0; }

template<typename T>
int deque<T>::count() const { return _size; }

template<typename T>
void deque<T>::push_back(const T& value) {
	_sys_assertd(_capacity > 0, "Capacity must be > 0 before push_back");
	if (_size == _capacity)
		grow();
	_array[_tail] = value;
	_tail = (_tail + 1) % _capacity;
	++_size;
}
template<typename T>
T& deque<T>::push_back_unsafe() {
	_sys_assertd(_capacity > 0, "Capacity must be > 0 before push_back");
	if (_size == _capacity)
		grow();
	T& result = _array[_tail];
	_sys_memset(&result, 0, sizeof(T));
	_tail = (_tail + 1) % _capacity;
	++_size;
	return result;
}

template<typename T>
T& deque<T>::push_back_default() {
	push_back(sys::default_value<T>());
	return tail();
}

template<typename T>
T& deque<T>::push_front_default() {
	push_back(sys::default_value<T>());
	return head();
}

template<typename T>
T deque<T>::dequeue_back() {
	_sys_assertd(_size > 0, "Cannot dequeue_back from empty deque");
	_tail = (_tail - 1 + _capacity) % _capacity;
	T item = _array[_tail];
	_array[_tail].~T();
	--_size;
	return item;
}

template<typename T>
T deque<T>::dequeue_back_move() {
	_sys_assertd(_size > 0, "Cannot dequeue_back_move from empty deque");
	_tail = (_tail - 1 + _capacity) % _capacity;
	T item = std::move(_array[_tail]);
	_array[_tail].~T();
	--_size;
	return item;
}

template<typename T>
T deque<T>::dequeue_front() {
	_sys_assertd(_size > 0, "Cannot dequeue_front from empty deque");
	T item = _array[_head];
	_array[_head].~T();
	_head = (_head + 1) % _capacity;
	--_size;
	return item;
}

template<typename T>
T deque<T>::dequeue_front_move() {
	_sys_assertd(_size > 0, "Cannot dequeue_front_move from empty deque");
	T item = std::move(_array[_head]);
	_array[_head].~T();
	_head = (_head + 1) % _capacity;
	--_size;
	return item;
}

template<typename T>
void deque<T>::push_front(const T& value) {
	_sys_assertd(_capacity > 0, "Capacity must be > 0 before push_front");
	if (_size == _capacity)
		grow();
	_head = (_head - 1 + _capacity) % _capacity;
	_array[_head] = value;
	++_size;
}

template<typename T>
void deque<T>::destroy_array() {
	_sys_assertd(_capacity >= 0, "Capacity must be non-negative");
	if (!_array) return;
	for (int i = 0; i < _size; ++i)
		std::_Destroy(&_array[(_head + i) % _capacity]);
	sys::memset(_array, 0, sizeof(T) * count());
	sys::free(_array);
	_array = nullptr;
}

template<typename T>
void deque<T>::_do_clone(deque<T>* other) const {
	_sys_assert(other);
	_sys_assertd(other != this, "Cannot clone deque into itself");
	other->ensure_capacity(this->_capacity);
	for (int i = 0; i < this->_size; ++i) {
		int index = (_head + i) % _capacity;
		other->push_back(_array[index]);
	}
}

template<typename T>
void deque<T>::clear() {
	destroy_array();
	_array = nullptr;
	_head = _tail = _size = _capacity = 0;
}

template<typename T>
const T& deque<T>::tail() const {
	_sys_assertd(_size > 0, "tail() called on empty deque");
	return _array[(_tail - 1 + _capacity) % _capacity];
}

template<typename T>
T& deque<T>::tail() {
	_sys_assertd(_size > 0, "tail() called on empty deque");
	return _array[(_tail - 1 + _capacity) % _capacity];
}

template<typename T>
const T& deque<T>::head() const {
	_sys_assertd(_size > 0, "head() called on empty deque");
	return _array[_head];
}

template<typename T>
T& deque<T>::head() {
	_sys_assertd(_size > 0, "head() called on empty deque");
	return _array[_head];
}

template<typename T>
const T& deque<T>::operator [](size_t i) const {
	_sys_assertd(i < (size_t)_size, "Index out of range");
	return _array[(_head + i) % _capacity];
}

template<typename T>
T& deque<T>::operator [](size_t i) {
	_sys_assertd(i < (size_t)_size, "Index out of range");
	return _array[(_head + i) % _capacity];
}

template<typename T>
void deque<T>::ensure_capacity(int required_capacity) {
	_sys_assertd(required_capacity >= 0, "ensure_capacity: negative capacity");
	if (_capacity < required_capacity)
		grow(required_capacity);
}

template<typename T>
void deque<T>::grow(int requiredCapacity) {
	_sys_assertd(requiredCapacity >= 0, "grow: negative capacity requested");
	const int MinimumGrow = 4;
	int newCapacity = std::min(DEQUE_MAX_CAPACITY, std::max((int)_capacity * 2, (int)_capacity + MinimumGrow));
	if (requiredCapacity > newCapacity && requiredCapacity < DEQUE_MAX_CAPACITY)
		newCapacity = requiredCapacity;
	_sys_assertd(newCapacity > _capacity, "grow: new capacity did not increase");
	T* newArray = (T*)sys::memalign(alignof(T), newCapacity * sizeof(T));
	if (!newArray)
		sys::abort_expresive(ENOMEM, "Could not allocate more memory. sz: %x", newCapacity * sizeof(T));
	if (_head == 0) {
		if (_array)
			sys::copy_objects_non_trivial(_array, newArray, _size);
	}
	else {
		if (_array) {
			sys::copy_objects_non_trivial(_array, _head, newArray, 0, _capacity - _head);
			sys::copy_objects_non_trivial(_array, 0, newArray, _capacity - _head, _tail);
		}
	}
	if (_size)
		destroy_array();
	_array = newArray;
	_head = 0;
	_tail = _size;
	_capacity = newCapacity;
}

template<typename T>
T& deque<T>::_unsafe_element_at(int index) const {
	_sys_assertd(index >= 0 && index < _size, "_unsafe_element_at: index out of range");
	return *(T*)(this->_array + index);
}

template<typename T>
bool deque<T>::equals(const deque<T>& other) const {
	if (other.count() != _size)
		return false;
	for (int i = 0; i < _size; i++) {
		if (!compare_objects(_unsafe_element_at(i), other._unsafe_element_at(i)))
			return false;
	}
	return true;
}

template<typename T>
deque<T>::~deque() {
	clear();
}

_SYS_ENS
