#ifndef CPPBOX_WRAPPER_HPP
#define CPPBOX_WRAPPER_HPP

#include <concepts>
#include <type_traits>

namespace cppbox {

/**
 * @brief A transparent wrapper type to hold an object reference.
 *
 * @tparam T
 */
template<typename T>
class Wrapper {
public:
    using type = T;

    /**
     * @brief Construct a wrapper.
     *
     * @param object_
     */
    explicit Wrapper(T& object_);

    /**
     * @brief Direct member access, e.g. `wrapper->method(...)`.
     *
     * @return T*
     */
    T* operator->() const;

    /**
     * @brief Pointer-like access, e.g. `(*wrapper)->method(...)`.
     *
     * @return T&
     */
    T& operator*() const;

    /**
     * @brief Implicit conversion to the underlying type allows it to be passed to functions expecting the wrapped type.
     *
     * @return T&
     */
    operator T&() const;

private:
    /**
     * @brief Hold a reference to the wrapped object.
     *
     */
    T& object_;
};

template<typename T>
struct is_wrapper : std::false_type {};

template<typename T>
struct is_wrapper<Wrapper<T>> : std::true_type {};

template<typename T>
concept IsWrapper = is_wrapper<std::remove_reference_t<T>>::value;

}

#include "cppbox/impl/wrapper.hpp"

#endif
