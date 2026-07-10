#pragma once
#include "iter.h"
#include "_ns.h"
#include "new"
#include "default_allocator.h"
_SYS_NS

/// <summary>
/// Representa una serie de objetos denominados por T, de tamaño fijo, y administrado de forma inteligente.
/// Provee métodos para administrar, extraer e intercambiar elementos de una colección.
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T >//, typename _Allocator_Ty = sys::default_allocator_t>
class collection {

	/// <summary>
	/// Collection of T in heap, for this instance.
	/// </summary>
	heap_iter<T> _iterator;

	//destructor_function _dtorForType{ nullptr };
	//flagset _flags{};
public:
	using element_type = typename sys::remove_extent<T>::type;


	collection() : _iterator(){}
	collection(const collection&) = delete;
	collection(size_t fixed_size) : _iterator(){
		if (fixed_size == 0)return;
		//__expect(fixed_size > 0);
		_iterator.assign_new_crt(fixed_size);
	}

	//explicit collection(sys::iter<T> vals) : collection(vals.size())
	//{
	//
	//	int indx = 0;
	//	for (T& val : vals) {
	//		_iterator.at(indx);
	//		indx++;
	//	}
	//}
	const T* data() const { return (T*)this->_iterator.ptr(); }
	T* data() { return (T*)this->_iterator.ptr(); }

	T* begin() { return _iterator.begin(); }
	const T* begin() const { return _iterator.begin(); }

	T* end() { return _iterator.end(); }
	const T* end() const { return _iterator.end(); }

	size_t fixed_size() const { return _iterator.size(); }

	const T& at(size_t index) const { return _iterator[index]; }
	T& at(size_t index) { return _iterator[index]; }

	sys::iter<const element_type> get_iterator() const {
		sys::iter<const element_type> val = nullptr;
		val._ptr = (const element_type*)this->begin();
		val._size = fixed_size();
		return val;
	}

	sys::iter<element_type> get_iterator() {
		sys::iter<element_type> val = nullptr;
		val._ptr = (element_type*)this->begin();
		val._size = fixed_size();
		return val;
	}

	void assign(const element_type* data, size_t data_count) {
		clear();

		if (data_count == 0) return;

		if (this->fixed_size() != data_count)
			resize(data_count);

		for (size_t i = 0; i < data_count++; i++)
			this->at(i) = data[i];

	}
	void set(element_type* new_data, size_t data_count) {
		clear();
		if (data_count == 0) return;
		// this->_iterator.assign_set_array_specific(new_data, data_count);
		// todo: fix this. Implement allocations policies for this collection.
	}
	void clear(size_t index)
	{
		element_type* arr = this->data();
		size_t count = this->fixed_size();

		if (index >= count)
			return;

		if (sys::is_compound<element_type>::value)
			sys::typed_destructor<element_type>(&arr[index]);

		size_t move_count = count - index - 1;

		if (move_count > 0)
		{
			//sys::memmove(&arr[index],&arr[index + 1],move_count * sizeof(T));
			for (int i = index; i < move_count; i++) {
				new (&arr[index]) element_type(arr[index + 1]);
				sys::memset(&arr[index + 1], 0, sizeof(T));
			}
		}

		sys::memset(&arr[count - 1], 0, sizeof(T));
	}


	void steal(collection<T>& other) {
		_iterator.steal(other._iterator);
	}


	void resize(size_t new_fixed_size)
	{

		if (new_fixed_size == 0)
		{
			_iterator.assign(nullptr);
			return;
		}

		size_t old_size = fixed_size();

		//_Allocator_Ty ator = _Allocator_Ty{};

		// todo: complete.
		sys::handle new_contents = nullptr;
		//sys::handle(sys::newx::allocate<element_type>(&ator, false));

		//new_contents._unsafe_assign(sys::newx::allocate<element_type[]>(&ator, new_fixed_size));


		// Remember: this exists, since calling original simplified and easier sys::newx::allocate causes 
		// compiler to blow up since we are already in a generic scope...
		// so factory_explicit functions avoid some redundant trait resolving.

		// Update 6/27/26: Update assignments to properly transfer the handle memory before 
		// his destruction is executed with remaining dynamic data.

		if (!sys::newx::is_typed<element_type>::value) // fundamentals.
		{
			// Instead of passing the result we need to explicitly pop the handle out.
			sys::handle new_fundamental_array_metadata=
				sys::newx::factory_explicit_allocate_array<element_type>(sys::default_allocator, new_fixed_size);

			new_contents._unsafe_assign(new_fundamental_array_metadata._unsafe_pop());

		}
		else { // typed. Classes
			 
			// Instead of passing the result we need to explicitly pop the handle out.
			sys::typed_handle<element_type> typed_array_metadata = sys::newx::factory_explicit_allocate_type_array<element_type>(sys::default_allocator, new_fixed_size);
			
			new_contents._unsafe_assign(typed_array_metadata._unsafe_pop());

		}

		// VALIDATION.
		__expect(new_contents.is_array());

		// Update: 6 27 26
		// Add another validation.
		__expect(new_contents.ptr() != NULL);


		//if (sys::newx::is_typed<element_type>::value) {
			//__expect(new_contents.is_typed());
		//}
		//sys::new_specific_array<T>(new_fixed_size,
			//heap_handle_flags::IsOwner |
			//heap_handle_flags::ReleaseOnRemove);
			

		//sys::handle new_contents =
		//	sys::new_heap_array<T>(new_fixed_size,
		//		heap_handle_flags::IsOwner |
		//		heap_handle_flags::ReleaseOnRemove);

		T* dst = (T*)new_contents.ptr();
		T* src = (T*)_iterator.hdl().ptr();

		size_t common =
			old_size < new_fixed_size ? old_size : new_fixed_size;

		for (size_t i = 0; i < common; i++)
			new(&dst[i]) T(src[i]);

		for (size_t i = common; i < new_fixed_size; i++)
			new(&dst[i]) T();

		for (size_t i = new_fixed_size; i < old_size; i++)
			sys::typed_destructor<T>(&src[i]);

		

		_iterator.hdl().steal(sys::move(new_contents));

	}


	void clear() {

		if (sys::is_compound<T>::value)
			for (size_t i = 0; i < fixed_size(); i++) clear(i);
		else
			sys::memset(this->_iterator.ptr(), 0, sizeof(T) * fixed_size());
		this->_iterator.assign(nullptr);
	}

	bool is_empty() const {
		return _iterator.is_empty();
	}
	static collection<T> empty() {
		return {};
	}
	const T& operator[](size_t index) const {
		return this->_iterator[index];
	}
	T& operator[](size_t index) {
		return this->_iterator[index];
	}
	collection<T>	operator =(const collection<T>& ) = delete;

	~collection() {
		clear();
	}
};

_SYS_ENS