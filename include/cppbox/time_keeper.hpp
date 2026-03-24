#ifndef CPPBOX_TIME_KEEPER_HPP
#define CPPBOX_TIME_KEEPER_HPP

#include <vector>

#include "cppbox/time.hpp"

namespace cppbox {

template<IsTimePoint Time_>
class TimeKeeperBase {
public:
    /**
     * @brief Time class
     *
     */
    using Time = Time_;

    /**
     * @brief Duration class
     *
     */
    using Duration = Time::duration;

    /**
     * @brief Get the end time.
     *
     * @return Time
     */
    virtual Time end() const = 0;

    /**
     * @brief Find the index for a given time, equal to i if the time at index i <= `time_`, or a negative integer if
     * time precedes `start()`. Note that very large times may induce overflow.
     *
     * @param time_ query time
     * @return int index
     */
    virtual int find_index(const Time time_) const = 0;

    /**
     * @brief Returns the time interval between the time at index i and the time at index i + 1
     *
     * @param index first index of the interval
     * @return Duration
     */
    virtual Duration interval(const int index) const;

    /**
     * @brief Reset the time keeper.
     *
     */
    virtual void reset() = 0;

    /**
     * @brief Get the start time.
     *
     * @return Time
     */
    virtual Time start() const = 0;

    /**
     * @brief Get the number of times
     *
     * @return int
     */
    virtual int size() const = 0;

    /**
     * @brief Get the time at index `i`.
     *
     * @param index
     * @return Time
     */
    virtual Time time(const int index) const = 0;
};

template<IsTimePoint Time_>
class OrderedTimeKeeper : public TimeKeeperBase<Time_> {
public:
    /**
     * @brief Base class
     *
     */
    using Base = TimeKeeperBase<Time_>;

    /**
     * @brief Time class
     *
     */
    using Time = Base::Time;

    /**
     * @brief Duration class
     *
     */
    using Duration = Base::Duration;

    /**
     * @brief Get the end time as the last time.
     *
     * @return Time
     */
    Time end() const override;

    /**
     * @brief Returns as the index as described by `TimeKeeperBase`, returning -1 if `time_` precedes `start()`.
     *
     * This has logarithmic complexity in the length of the stored times.
     *
     * @param time_
     * @return int
     */
    int find_index(const Time time_) const override;

    /**
     * @brief Add a time to the end of the stored times.
     *
     * @param time_
     */
    void push_back(const Time time_);

    /**
     * @brief Reset the time keeper, clearing any stored data.
     *
     */
    void reset() override;

    /**
     * @brief Get the start time as the first time.
     *
     * @return Time
     */
    Time start() const override;

    /**
     * @brief Get the number of times.
     *
     * @return int
     */
    int size() const override;

    /**
     * @brief Get all times.
     *
     * @return const std::vector<Time>&
     */
    const std::vector<Time>& times() const;

    /**
     * @brief Get the time at index `i`.
     *
     * @param index index
     * @return Time time
     */
    Time time(const int index) const override;

private:
    /**
     * @brief Stored times.
     *
     */
    std::vector<Time> times_;
};

template<IsTimePoint Time_>
class UniformTimeKeeper : public TimeKeeperBase<Time_> {
public:
    /**
     * @brief Base class
     *
     */
    using Base = TimeKeeperBase<Time_>;

    /**
     * @brief Time class
     *
     */
    using Time = Base::Time;

    /**
     * @brief Duration class
     *
     */
    using Duration = Base::Duration;

    /**
     * @brief Construct a Uniform Time Keeper with start time 0 and interval of 1 second.
     *
     */
    explicit UniformTimeKeeper();

    /**
     * @brief Construct a new Uniform Time Keeper.
     *
     * @param start_
     * @param interval_
     */
    explicit UniformTimeKeeper(const Time start_, const Duration interval_);

    /**
     * @brief Get the end time as the max of `Time`, which may not be an integer number of intervals from start.
     *
     * @return Time
     */
    Time end() const override;

    /**
     * @brief Returns as the index as described by `TimeKeeperBase`, returning a negative integer if `time_` precedes
     * `start()` according to the number of intervals behind `start()` it is (e.g. -1 in the first interval before
     * `start()`).
     *
     * This has constant complexity.
     *
     * @param time_
     * @return int
     */
    int find_index(const Time time_) const override;

    /**
     * @brief Get the interval between times.
     *
     * @return Duration
     */
    Duration interval(const int) const override;

    /**
     * @brief Get the interval between times.
     *
     * @return Duration
     */
    Duration interval() const;

    /**
     * @brief Reset the time keeper, clearing any stored data (no-op for UniformTimeKeeper).
     *
     */
    void reset() override;

    /**
     * @brief Get the start time as the stored start time.
     *
     * @return Time
     */
    Time start() const override;

    /**
     * @brief Get the number of times. The result is always std::numeric_limits<int>::max() avoiding
     * computations that may have integer overflow. Note that `time(size() - 1)` may not be well defined.
     *
     * @return int
     */
    int size() const override;

    /**
     * @brief Get the time at index `i`.
     *
     * @param index index
     * @return Time time
     */
    Time time(const int index) const;

private:
    /**
     * @brief Start time.
     *
     */
    Time start_;

    /**
     * @brief Interval between times.
     *
     */
    Duration interval_;
};

}

#include "cppbox/impl/time_keeper.hpp"

#endif
