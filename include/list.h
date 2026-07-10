#pragma once
#include "_ns.h"
#include "memory.h"
#include "aligned_storage.h"
#include "allocator.h"
#include "traits.h"
#include "algorithm.h"
#include "collection.h"
#include "unexpect.h"
_SYS_NS
template<typename T>
class list  {
    collection<T> _content;
    size_t _length{ 0 };

public:

    /**
     * @brief Constructs an uninitialized list.
     *
     * Does not allocate memory. Internal storage remains null.
     */
    list() : _content(), _length{0} {}


    /**
     * @brief Move-constructs this list by stealing another instance.
     *
     * @param other Source list to steal from.
     */
    list(list& other) { steal(other); }

    /// Copy construction is disabled.
    list(const list&) = delete;

    /**
     * @brief Constructs a list from an iterator range.
     *
     * @param iter Iterator descriptor containing pointer and size.
     */
    list(sys::iter<T> iter) {
        this->assign(iter);
    }

    /**
     * @brief Constructs a list with a predefined capacity.
     *
     * @param capacity Number of elements to allocate space for.
     */
    list(size_t capacity) {
        resize(capacity);
    }

    T* push_back(const T& value) {
        ensure_capacity(size() + 1);
        __expect(this->_content.data() != NULL);
        this->_content[_length] = value;
        _length++;
        return &this->_content[_length - 1];
    }

    /**
     * @brief Ensures the internal storage can hold at least the specified number of elements.
     *
     * Automatically grows capacity (typically doubling).
     *
     * @param size Required minimum capacity.
     */
    void ensure_capacity(size_t size) {
        
        // Update 6 27 26: this segment only works if capacity is already nonzero.
        if (size >= capacity())
            this->_content.resize(capacity() + (capacity() >> 1));

        // If the collection isnt assigned yet. Fixed resize 
        if (capacity() == 0)
            this->_content.resize(8);

        // Add some validations.
        __expect(this->data() != NULL);
        __expect(this->capacity() > 0);
    }

    /**
     * @brief Assigns a raw memory buffer as backing storage.
     *
     * @param data_raw_new Pointer to external memory.
     * @param count Number of elements in buffer.
     */
    void set_specific(T* data_raw_new, size_t count) {
        _content.set(data_raw_new, count);
        _length = count;
        ensure_capacity(size() + 1);
    }

    T& back() { return this->_content.at(this->_length - 1); }
    const T& back() const{ return this->_content.at(this->_length - 1); }

    T& front() { return this->_content.at(0); }
    const T& front() const { return this->_content.at(0); }
    T pull_back() {
        T r = this->_content[this->_length - 1];
        this->_content.clear(this->_length - 1);
        this->_length--;
        return r;
    }
    void pop_back() {
        this->_content.clear(this->_length - 1);
        this->_length--;
    }

    T* add(const T& value) {
        ensure_capacity(size() + 1);
        __expect(this->_content.data() != NULL);
        this->_content[_length] = value;
        _length++;
        return &this->_content[_length - 1];
    }

    /**
     * @brief Adds a copy of the referenced element to the list.
     *
     * If the pointer already belongs to this list, insertion is skipped.
     *
     * @param reference Pointer to element to copy.
     * @return Pointer to the inserted element, or nullptr if skipped.
     */
   T* add(T* reference) {
        if (contains(reference)) return false;
        ensure_capacity(size() + 1);
        __expect(this->_content.data() != NULL);
        this->_content[_length] = *reference;
        _length++;
        return &this->_content[_length - 1];
    }

    /**
     * @brief Removes an element from the list.
     *
     * If the pointer does not belong to the list, a value-based comparison is performed.
     *
     * @param reference Pointer or value reference to remove.
     * @return True if element was removed.
     */
    bool remove(T* reference) {
        int32_t indx = find_index(reference);
        if (indx == -1) return false;
        this->_content.clear(indx);
        _length--;
        return true;
    }
    
    bool remove_at(size_t index) {
        if (index >= _length) FAIL("Index out of range.");

        this->_content.clear(index);
        _length--;
        return true;
    }

    /**
     * @brief Checks whether an element exists in the list.
     *
     * Performs pointer-range check first, then falls back to equality comparison.
     *
     * @param reference Pointer to element.
     * @return True if found.
     */
    bool contains(T* reference) {
        if (begin() <= reference && end() >= reference) return true;

        T& right = *reference;
        for (T& other : this->_content) {
            if (other == right) return true;
        }
        return false;
    }

    /**
     * @brief Finds the index of an element.
     *
     * Supports pointer-based lookup or value comparison.
     *
     * @param reference Pointer to element.
     * @return Index if found, otherwise -1.
     */
    int32_t find_index(T* reference) {
        if (begin() <= reference && end() >= reference) {
            return (int32_t)static_cast<ptrdiff_t>(end() - reference) / sizeof(T);
        }

        int32_t i = 0;
        T& right = *reference;
        for (T& other : this->_content) {
            if (other == right) return i;
            ++i;
        }
        return -1;
    }

    /**
     * @brief Clears all elements from the list.
     */
    void clear() {
        _content.clear();
        _length = 0;
    }

    /**
     * @brief Shrinks capacity to match current size.
     *
     * @return Reference to this list.
     */
    list& trim_excess() {
        _content.resize(this->size());
        return *this;
    }

    /**
     * @brief Reverses the order of elements.
     *
     * @return Reference to this list.
     */
    list& reverse() {
        collection<T> new_collection{ this->size() };
        for (int i = 0; i < this->size(); i++) {
            new_collection[this->size() - i] = _content[i];
        }
        _content.steal(new_collection);
        return *this;
    }

    /**
     * @brief Resizes internal capacity.
     *
     * @param capacity New capacity.
     */
    list& resize(size_t capacity) {
        this->_content.resize(capacity);
        _length = sys::min(_length, capacity);
        return *this;
    }

    /**
     * @brief Reserves capacity without shrinking.
     */
    list& reserve(size_t capacity) {
        if (this->capacity() < capacity)
            resize(capacity);
        return *this;
    }

    /// @brief Returns pointer to raw data.
    const T* data() const { return this->_content.data(); }
    T* data() { return this->_content.data(); }

    /// @brief Iterator begin.
    T* begin() { return this->data(); }

    /// @brief Iterator end.
    T* end() { return this->data() + _length; }

    const T* begin() const { return this->data(); }
    const T* end() const { return this->data() + _length; }

    /**
     * @brief Assigns content from another list.
     */
    void assign(list<T>& other) {
        _content.assign(other.data(), other._length);
        this->_length = other._length;
    }

    /**
     * @brief Assigns from iterator range.
     */
    void assign(sys::iter<T> elems) {
        _content.assign(elems.begin(), elems._size);
        this->_length = elems._size;
    }

    /**
     * @brief Steals memory and contents from another list.
     */
    void steal(list<T>& other) {
        this->_content.steal(other._content);
        this->_length = other._length;
        other._length = 0;
    }

    /// @brief Returns number of elements.
    size_t size() const {
        return this->_length;
    }

    /// @brief Returns allocated capacity.
    size_t capacity() const {
        return this->_content.fixed_size();
    }

    list& operator=(const list&) = delete;

    /*
        Warning: This is an implementation of an exclusive assignment heuristic for "Tidy" factories, 
        derived from framework functionality,
        and it should not be used in general implementations.

        This instance will adopt the information from the source object—which is
        subsequently invalidated—resulting in a transfer once the object's state 
        is definitively established.

       */
    void _unsafe_assign(sys::collection<T>& other, int32_t length) {
        this->_content.steal(other);
        this->_length = length;
    }

    /**
     * @brief Move assignment via steal.
     */
    list& operator=(list& other) {
        steal(other);
        return *this;
    }
    T& operator[](size_t i) {return this->_content.at(i);}
    const T& operator[](size_t i) const {return this->_content.at(i);}
};

_SYS_ENS
