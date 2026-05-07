#ifndef CPPBOX_IMPL_WRAPPER_HPP
#define CPPBOX_IMPL_WRAPPER_HPP

#include "cppbox/wrapper.hpp"

namespace cppbox {

template<typename T>
Wrapper<T>::Wrapper(T& object_) : object_(object_) {}

template<typename T>
T* Wrapper<T>::operator->() const {
    return &object_;
}

template<typename T>
T& Wrapper<T>::operator*() const {
    return object_;
}

template<typename T>
Wrapper<T>::operator T&() const {
    return object_;
}

}

#endif
