#ifndef CPPBOX_TEMPORAL_VECTOR_HPP
#define CPPBOX_TEMPORAL_VECTOR_HPP

#include <deque>
#include <type_traits>

#include "cppbox/time.hpp"
#include "cppbox/time_keeper.hpp"

namespace cppbox {

template<typename Element_, IsTimeKeeper TimeKeeper_>
class TemporalVectorBase {
public:
    /**
     * @brief Element class.
     *
     */
    using Element = Element_;

    /**
     * @brief Time keeper class.
     *
     */
    using TimeKeeper = TimeKeeper_;

    /**
     * @brief Time class.
     *
     */
    using Time = TimeKeeper::Time;

    /**
     * @brief Duration class.
     *
     */
    using Duration = TimeKeeper::Duration;

    /**
     * @brief Change the start time. Throws an exception if change is invalid.
     *
     * @param index
     * @param time_
     */
    void change_start_time(const Time time_);

    /**
     * @brief Get immutable last element
     *
     * @return const Element&
     */
    const Element& element_back() const;

    /**
     * @brief Get mutable last element
     *
     * @return Element&
     */
    Element& element_back();

    /**
     * @brief Get immutable first element
     *
     * @return const Element&
     */
    const Element& element_front() const;

    /**
     * @brief Get mutable first element
     *
     * @return Element&
     */
    Element& element_front();

    /**
     * @brief Get immutable vector of elements.
     *
     * @return const std::deque<Element>&
     */
    const std::deque<Element>& elements() const;

    /**
     * @brief Get mutable elements.
     *
     * @return std::deque<Element>&
     */
    std::deque<Element>& elements();

    /**
     * @brief Get immutable element at a specific index.
     *
     * @param i index
     * @return const Element&
     */
    const Element& element(const std::size_t i) const;

    /**
     * @brief Get mutable element at a specific index.
     *
     * @param i index
     * @return Element&
     */
    Element& element(const std::size_t i);

    /**
     * @brief Check if element is empty.
     *
     * @return true
     * @return false
     */
    bool empty() const;

    /**
     * @brief Time corresponding to the last state, equivalent to `time_keeper().time(size() - 1)`, which is not
     * necessarily equal to `time_keeper().end()`.
     *
     * @return Time
     */
    Time end_time() const;

    /**
     * @brief Reset elements and time keeper.
     *
     */
    void reset();

    /**
     * @brief Number of elements.
     *
     * @return std::size_t
     */
    std::size_t size() const;

    /**
     * @brief Time corresponding to the first state, equivalent to `time_keeper().time(0)`.
     *
     * @return Time
     */
    Time start_time() const;

    /**
     * @brief Get immutable time keeper.
     *
     * @return const TimeKeeper&
     */
    const TimeKeeper& time_keeper() const;

    /**
     * @brief Get a copy of the times as vector.
     *
     * @return std::vector<Time>
     */
    std::vector<Time> times() const;

    /**
     * @brief Get a copy of the time at a specific index.
     *
     * @param i
     * @return Time
     */
    Time time(const int i) const;

protected:
    /**
     * @brief Protected constructor for abstract base class.
     *
     * @param time_keeper_
     */
    explicit TemporalVectorBase(const TimeKeeper& time_keeper_);

    /**
     * @brief Helper function for derived types to emplace element into storage.
     *
     * @tparam Args
     * @param args
     */
    template<class... Args>
    void emplace_back(Args&&... args);

    /**
     * @brief Stored elements.
     *
     * Note: One reason not to use std::vector<Element> is that it is specialised for `bool` and does not return true
     * references.
     *
     */
    std::deque<Element> elements_;

    /**
     * @brief Time keeper.
     *
     */
    TimeKeeper time_keeper_;
};

template<typename Element_, typename Time_>
class OrderedTemporalVector : public TemporalVectorBase<Element_, OrderedTimeKeeper<Time_>> {
public:
    /**
     * @brief Base class.
     *
     */
    using Base = TemporalVectorBase<Element_, OrderedTimeKeeper<Time_>>;
    using typename Base::Duration;
    using typename Base::Element;
    using typename Base::Time;
    using typename Base::TimeKeeper;

    /**
     * @brief Construct an ordered temporal vector storage container.
     *
     */
    explicit OrderedTemporalVector();

    /**
     * @brief Change the end time. Throws an exception if change is invalid.
     *
     * @param time_
     */
    void change_end_time(const Time time_);

    /**
     * @brief Change the time at a specific index. Throws an exception if change is invalid.
     *
     * @param index
     * @param time_
     */
    void change_time(const int index, const Time time_);

    /**
     * @brief Add a time-element pair to storage.
     *
     * @tparam Args
     * @param time_
     * @param args
     */
    template<class... Args>
    void emplace_back(const Time time_, Args&&... args);
};

template<typename Element_, typename Time_>
class UniformTemporalVector : public TemporalVectorBase<Element_, UniformTimeKeeper<Time_>> {
public:
    /**
     * @brief Base class.
     *
     */
    using Base = TemporalVectorBase<Element_, UniformTimeKeeper<Time_>>;
    using typename Base::Duration;
    using typename Base::Element;
    using typename Base::Time;
    using typename Base::TimeKeeper;

    /**
     * @brief Construct a uniform temporal vector storage container.
     *
     * @param start_
     * @param interval_
     */
    explicit UniformTemporalVector(const Time start_, const Duration interval_);

    /**
     * @brief Construct a uniform temporal vector storage container.
     *
     * @param time_keeper_
     */
    explicit UniformTemporalVector(const TimeKeeper& time_keeper_);

    /**
     * @brief Add time-element pair to storage at the next (uniformly-spaced) time.
     *
     */
    using Base::emplace_back;
};

}

#include "cppbox/impl/temporal_vector.hpp"

#endif
