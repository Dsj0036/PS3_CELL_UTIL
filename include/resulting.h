#pragma once
#include "optional.h"
#include <cell/error.h>
#include "error_code.h"
namespace sys {

    /**
     * @brief Represents the result of a system-level operation.
     *
     * This class encapsulates a system error code (`CellError`) together with
     * an optional value of type `_Ty`.
     *
     * It is intended for low-level APIs where a function may either:
     *  - return a valid object, or
     *  - fail and provide a system error code.
     *
     * Unlike asynchronous result types, this class is designed strictly
     * for immediate, synchronous system call outcomes.
     *
     * @tparam _Ty Type of the contained value.
     */
    template<class _Ty>
    class result {

        /// Stored optional result object.
        sys::optional<_Ty> _result{};

        /// System error code associated with this result.
        CellError _num{ 0 };

    public:
		explicit result(CellError failure) : _result(nullopt), _num(failure) {}

        /**
         * @brief Constructs an empty result with no value.
         *
         * The error code is initialized to zero.
         */
        result(nullopt_t) : _result(nullopt) {}

        /**
         * @brief Default constructor.
         *
         * Constructs an empty result equivalent to result(nullopt).
         */
        result() : result(nullopt) {}

        /**
         * @brief Move constructor.
         *
         * Transfers both the stored value and error code from another result.
         * The source object is reset after the move.
         *
         * @param other Result to move from.
         */
        result(result&& other)
            : _num(other._num),
            _result(other._result)
        {
            other.reset();
        }

        /**
         * @brief Constructs a successful result containing a value.
         *
         * The error code is left as zero.
         *
         * @param in Value to store.
         */
        result(const _Ty& in)
            : _result(in)
        {
        }
        /**
         * @brief Constructs a successful result containing a value.
         *
         * The error code is left as zero.
         *
         * @param in Value to store.
         */
        result(_Ty&& in)
            : _result(in)
        {
        }

        /**
         * @brief Copy construction is disabled.
         */
        result(const result&) = delete;

        /**
         * @brief Assigns an error code to the result.
         *
         * Does not modify the stored value.
         *
         * @param r System error code.
         * @return Reference to this object.
         */
        inline result& with_code(CellError r) {
            this->_num = r;
            return *this;
        }

        /**
         * @brief Copies the contents from another result.
         *
         * Both the value and the error code are copied.
         *
         * @param other Source result.
         */
        void reset(result& other) {
            _result = other._result;
            _num = other._num;
        }

        bool is_failure()const {
            return sys::is_failure(this->_num);
        }

        /**
         * @brief Clears the result.
         *
         * Resets the stored value and sets the error code to zero.
         */
        void reset() {
            _num = 0;
            _result.reset();
        }

        /**
         * @brief Assigns an error code to this result.
         *
         * The stored value is cleared before assigning the code.
         *
         * @param other Error code to assign.
         * @return Reference to this object.
         */
        result& operator =(CellError other) {
            reset();
            return with_code(other);
        }



        /**
         * @brief Move assignment operator.
         *
         * Reconstructs this object using placement new.
         *
         * @param other Result to move from.
         * @return Reference to this object.
         */
        result& operator =(result&& other) {
            new (this) result(sys::move(other));
            return *this;
        }

        /**
         * @brief Returns the stored error code.
         *
         * @return Reference to the internal error code.
         */
        inline const CellError& code() const { return _num; }
        inline CellError& code() { return _num; }

        /**
         * @brief Returns the stored value (optional).
         *
         * @return Reference to the internal optional object.
         */
        inline sys::optional<_Ty>& object() { return _result; }

        /**
         * @brief Returns the stored value (optional) as const.
         *
         * @return Const reference to the internal optional object.
         */
        inline const sys::optional<_Ty>& object() const { return _result; }



    };

}