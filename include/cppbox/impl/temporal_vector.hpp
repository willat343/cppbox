#ifndef CPPBOX_IMPL_TEMPORAL_VECTOR_HPP
#define CPPBOX_IMPL_TEMPORAL_VECTOR_HPP

#include <utility>

#include "cppbox/temporal_vector.hpp"

namespace cppbox {

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::elements() const -> const std::vector<Element>& {
    return elements_;
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::elements() -> std::vector<Element>& {
    return const_cast<std::vector<Element>&>(std::as_const(*this).elements());
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::element_back() const -> const Element& {
    return elements().back();
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::element_back() -> Element& {
    return const_cast<Element&>(std::as_const(*this).element_back());
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::element_front() const -> const Element& {
    return elements().front();
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::element_front() -> Element& {
    return const_cast<Element&>(std::as_const(*this).element_front());
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::element(const std::size_t i) const -> const Element& {
    return elements().at(i);
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::element(const std::size_t i) -> Element& {
    return const_cast<Element&>(std::as_const(*this).element(i));
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::end_time() const -> Time {
    return time_keeper().time(size() - 1);
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline bool TemporalVectorBase<Element_, TimeKeeper_>::empty() const {
    return elements().empty();
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline void TemporalVectorBase<Element_, TimeKeeper_>::reset() {
    elements().clear();
    time_keeper_.reset();
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline std::size_t TemporalVectorBase<Element_, TimeKeeper_>::size() const {
    return elements().size();
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::start_time() const -> Time {
    return time_keeper().time(0);
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::time_keeper() const -> const TimeKeeper& {
    return time_keeper_;
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::times() const -> std::vector<Time> {
    const std::size_t size_ = size();
    std::vector<Time> times_(size_);
    for (std::size_t i = 0; i < size_; ++i) {
        times_[i] = time(i);
    }
    return times_;
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
inline auto TemporalVectorBase<Element_, TimeKeeper_>::time(const int i) const -> Time {
    return time_keeper().time(i);
}

template<typename Element_, IsTimeKeeper TimeKeeper_>
TemporalVectorBase<Element_, TimeKeeper_>::TemporalVectorBase(const TimeKeeper& time_keeper_)
    : time_keeper_(time_keeper_) {}

template<typename Element_, IsTimeKeeper TimeKeeper_>
template<class... Args>
inline void TemporalVectorBase<Element_, TimeKeeper_>::emplace_back(Args&&... args) {
    elements_.emplace_back(std::forward<Args>(args)...);
}

template<typename Element_, typename Time_>
inline OrderedTemporalVector<Element_, Time_>::OrderedTemporalVector() : Base(TimeKeeper()) {}

template<typename Element_, typename Time_>
template<class... Args>
inline void OrderedTemporalVector<Element_, Time_>::emplace_back(const Time time, Args&&... args) {
    this->time_keeper_.push_back(time);
    Base::template emplace_back(std::forward<Args>(args)...);
}

template<typename Element_, typename Time_>
inline UniformTemporalVector<Element_, Time_>::UniformTemporalVector(const Time start_, const Duration interval_)
    : UniformTemporalVector(TimeKeeper(start_, interval_)) {}

template<typename Element_, typename Time_>
inline UniformTemporalVector<Element_, Time_>::UniformTemporalVector(const TimeKeeper& time_keeper_)
    : Base(time_keeper_) {}

}

#endif
