#ifndef CPPBOX_IMPL_MONOTONIC_HPP
#define CPPBOX_IMPL_MONOTONIC_HPP

#include "cppbox/monotonic.hpp"

namespace cppbox {

template<typename T>
inline MonotonicIncreasing<T>::MonotonicIncreasing(const_reference value_) : value_(value_) {}

template<typename T>
inline void MonotonicIncreasing<T>::try_update(const_reference new_value) {
    if (new_value >= value_) {
        value_ = new_value;
    }
}

template<typename T>
inline void MonotonicIncreasing<T>::update(const_reference new_value) {
    throw_if(new_value < value_, "Value must monotonically increase.");
    value_ = new_value;
}

template<typename T>
inline auto MonotonicIncreasing<T>::value() const -> const_reference {
    return value_;
}

}

#endif
