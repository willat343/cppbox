#ifndef CPPBOX_MONOTONIC_HPP
#define CPPBOX_MONOTONIC_HPP

namespace cppbox {

template<typename T>
class MonotonicIncreasing {
public:
    using type = T;
    using reference = T&;
    using const_reference = const T&;

    explicit MonotonicIncreasing() = default;

    explicit MonotonicIncreasing(const_reference value_);

    void try_update(const_reference new_value);

    void update(const_reference new_value);

    const_reference value() const;

private:
    type value_;
};

}

#include "cppbox/impl/monotonic.hpp"

#endif
