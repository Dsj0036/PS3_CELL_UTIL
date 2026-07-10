#pragma once
#include "..\_ns.h"
#include "shared_ptr.h"
#include "..\traits.h"
_SYS_NS

namespace detail {

    template<typename T>
    sys::enable_if_t<
        sys::is_array<T>::value,
        sys::shared_ptr<T>
    >
        make_shared(size_t array_size, sys::alloc* allocator)
    {
        using element_t = typename sys::remove_extent_t<T>;

        auto* stcb =
            (_shared_typed_array_control_block*)
            sys::detail::factory::allocate_type_array(
                array_size,
                sizeof(element_t),
                alignment_of<element_t>::value,
                allocator,
                &typed_destructor<element_t>,
                true
            );

        stcb->retain();

        for (size_t i = 0; i < array_size; i++)
            new (&((element_t*)stcb->_px)[i]) element_t();

        return sys::shared_ptr<T>(stcb);
    }

    template<typename T, typename ...Args>
    sys::enable_if_t<
        !sys::is_array<T>::value&&
        sys::is_compound<T>::value,
        sys::shared_ptr<T>
    >
        make_shared(sys::alloc* allocator, Args... r)
    {
        auto* stcb =
            (_shared_typed_control_block*)
            factory::allocate_type(
                sizeof(T),
                alignof(T),
                allocator,
                &typed_destructor<T>,
                true
            );

        stcb->retain();

        new (stcb->data()) T(r...);

        return sys::shared_ptr<T>((_control_block*)stcb);
    }


}

template<typename T, typename ...Args>
typename sys::enable_if_t<can_be_shared<T>::value, sys::shared_ptr<T>> make_shared(sys::alloc* allocator, Args...s) {

	return detail::make_shared<T>(allocator, s...);
}



_SYS_ENS