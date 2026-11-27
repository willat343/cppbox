#ifndef CPPBOX_IMPL_CLASSIFIERS_HPP
#define CPPBOX_IMPL_CLASSIFIERS_HPP

#include <stdexcept>

#include "cppbox/classifiers.hpp"
#include "cppbox/exceptions.hpp"

namespace cppbox {

template<std::totally_ordered T_>
inline ThresholdClassifier<T_>::ThresholdClassifier(const T& threshold_) : threshold_(threshold_) {}

template<std::totally_ordered T_>
inline bool ThresholdClassifier<T_>::classify(const T& value) {
    return value > threshold_;
}

template<std::totally_ordered T_>
inline auto ThresholdClassifier<T_>::threshold() const -> const T& {
    return threshold_;
}

template<std::totally_ordered T_>
inline SchmittTrigger<T_>::SchmittTrigger(const T& falling_threshold_, const T& rising_threshold_, const bool state_)
    : falling_threshold_(falling_threshold_), rising_threshold_(rising_threshold_), state_(state_) {
    throw_if(!(falling_threshold_ <= rising_threshold_),
            "Schmitt trigger falling threshold must be less than or equal to its rising threshold.",
            std::invalid_argument);
}

template<std::totally_ordered T_>
inline bool SchmittTrigger<T_>::classify(const T& value) {
    if (value > rising_threshold_) {
        state_ = true;
    } else if (value < falling_threshold_) {
        state_ = false;
    }
    return state_;
}

template<std::totally_ordered T_>
inline auto SchmittTrigger<T_>::falling_threshold() const -> const T& {
    return falling_threshold_;
}

template<std::totally_ordered T_>
inline auto SchmittTrigger<T_>::rising_threshold() const -> const T& {
    return rising_threshold_;
}

template<std::totally_ordered T_>
inline void SchmittTrigger<T_>::set_state(const bool state_) {
    this->state_ = state_;
}

template<std::totally_ordered T_>
inline bool SchmittTrigger<T_>::state() const {
    return state_;
}

}

#endif
