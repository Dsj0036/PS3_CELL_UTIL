#pragma once 
#include "include/vector.h"

namespace GC {

	struct refcount {
		int count = 1;  // Inicializa en 1 para la primera referencia
	};

	template<typename T>
	class shared_instance {
	public:
		T* object;
		mutable refcount* refs;

		shared_instance() : object(nullptr), refs(nullptr) {}

		shared_instance(T* obj) : object(obj), refs(new refcount()) {
			refs->count = 1;
		}

		shared_instance(const shared_instance<T>& instance) {
			object = instance.object;
			refs = instance.refs;
			if (refs) refs->count++;
		}

		~shared_instance();

		bool notnull() const {
			return object != nullptr;
		}

		T* get() {
			return object;
		}

		int count() const {
			return refs ? refs->count : 0;
		}

		int addref() {
			return refs ? ++refs->count : 0;
		}

		int release_ref() {
			if (refs->count == -1u) {
				refs->count = 0;
			}
			return refs ? --refs->count : 0;
		}

		// Conversión a un shared_instance<void> seguro
		operator shared_instance<void>() {
			shared_instance<void> untyped;
			untyped.object = this->object;
			untyped.refs = this->refs;
			untyped.addref();
			return untyped;
		}

		shared_instance<void> untyped() {
			return *this;
		}

		template<typename U>
		shared_instance<U> cast() {
			shared_instance<U> typed;
			typed.object = static_cast<U*>(this->object);
			typed.refs = this->refs;
			if (typed.refs) typed.addref(); // Mantener referencia
			return typed;
		}
	};

	vector<shared_instance<void>> dynamics;

	void collect() {
		int collected = 0;
		forIndexIn(dynamics.size()) {
			if (dynamics[i].count() == 0) {
				dynamics.remove_at(i);
				collected++;
			}
		}
	}

	template<typename T>
	class sptr {
		shared_instance<T> counted_instance;
	public:
		sptr() = delete;
		sptr(no_init) : counted_instance() {} // Constructor sin inicialización

		sptr(const sptr<T>& r) : counted_instance(r.counted_instance) {
			counted_instance.addref();
		}

		sptr(shared_instance<T> object_owner) : counted_instance(object_owner) {
			counted_instance.addref();
		}

		~sptr() {
			if (counted_instance.release_ref() == 0) {
				GC::collect();
			}
		}
		T& operator *() {
			return *counted_instance.get();
		}
		T* get() const {
			return counted_instance.get();
		}
		T* get() {
			return counted_instance.get();
		}

		T* operator->() const {
			return counted_instance.get();
		}
		T* operator->() {
			return counted_instance.get();
		}
	};

	template<typename T>
	shared_instance<T> initialize(T* px) {
		shared_instance<T> instance(px);
		instance.release_ref();
		dynamics.push_back(instance.untyped());

		return instance;
	}

	template<typename T>
	sptr<T> gcnew() {
		T* ins = reinterpret_cast<T*>(_sys_memalign(16, sizeof(T)));
		return sptr<T>(initialize(ins));
	}
	template<typename T>
	shared_instance<T>::~shared_instance() {
		if (refs && this->release_ref() == 0) {
			for (int i = 0; i < dynamics.size(); i++) {
				if (dynamics[i].object == this->object) {
					dynamics.remove_at(i);
				}
			}
			delete object;
			delete refs;
		}
	}
}

template<typename T>
using Object = GC::sptr<T>;

// Creates a new managed object.
template<typename T>
Object<T> gcnew() {
	return GC::gcnew<T>();
}
