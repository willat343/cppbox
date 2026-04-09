#ifndef CPPBOX_TIME_KEEPER_HPP
#define CPPBOX_TIME_KEEPER_HPP

#include <type_traits>
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
     * @brief Change the start time.
     *
     * @param time_
     */
    virtual void change_start_time(const Time time_) = 0;

    /**
     * @brief Check if there are any times (i.e., equivalent to `size() == 0`).
     *
     * @return true
     * @return false
     */
    bool empty() const;

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
     * @brief Check if `time_` exists (exactly).
     *
     * See also `bool has_time_within(const Time) const` and `void require_time(const Time)`.
     *
     * @param time_
     * @return true
     * @return false
     */
    virtual bool has_time(const Time time_) const;

    /**
     * @brief Check if `time_` exists or is between two times.
     *
     * @param time_
     * @return true
     * @return false
     */
    virtual bool has_time_within(const Time time_) const;

    /**
     * @brief Returns the time interval between the time at index i and the time at index i + 1
     *
     * @param index first index of the interval
     * @return Duration
     */
    virtual Duration interval(const int index) const;

    /**
     * @brief Ensure that `time_` exists (exactly). If the `time_` does not exist, add it if possible and otherwise
     * throw an exception.
     *
     * See also `bool has_time(const Time) const`.
     *
     * @param time_
     */
    virtual void require_time(const Time time_) = 0;

    /**
     * @brief Ensure that `time_` exists  or is between two times. If the `time_` does not exist, add it if possible and
     * otherwise throw an exception.
     *
     * @param time_
     */
    virtual void require_time_within(const Time time_) = 0;

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

template<typename T, typename Time = T::Time>
concept IsTimeKeeper = std::is_base_of_v<TimeKeeperBase<Time>, T>;

template<IsTimePoint Time_>
class OrderedTimeKeeper : public TimeKeeperBase<Time_> {
public:
    /**
     * @brief Base class
     *
     */
    using Base = TimeKeeperBase<Time_>;
    using typename Base::Duration;
    using typename Base::Time;

    /**
     * @brief Change the end time. Throws an exception if monotonicity would be violated.
     *
     * @param time_
     */
    virtual void change_end_time(const Time time_);

    /**
     * @brief Change the start time. Throws an exception if monotonicity would be violated.
     *
     * @param time_
     */
    void change_start_time(const Time time_) override;

    /**
     * @brief Change the time at a specific index. Throws an exception if index is invalid or monotonicity would be
     * violated.
     *
     * @param index
     * @param time_
     */
    virtual void change_time(const int index, const Time time_);

    /**
     * @brief Get the end time as the last stored time.
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
    virtual void push_back(const Time time_);

    /**
     * @brief Check if `time_` exists. If it doesn't and `time_` is >= `end()`, then add it. Otherwise, throw an
     * exception.
     *
     * @param time_
     */
    void require_time(const Time time_) override;

    /**
     * @brief Check if `time_` exists or is between two times. If it doesn't and `time_` is >= `end()`, then add it.
     * Otherwise, throw an exception.
     *
     * @param time_
     */
    void require_time_within(const Time time_) override;

    /**
     * @brief Reset the time keeper, clearing any stored data.
     *
     */
    void reset() override;

    /**
     * @brief Get the number of times.
     *
     * @return int
     */
    int size() const override;

    /**
     * @brief Get the start time as the first stored time.
     *
     * @return Time
     */
    Time start() const override;

    /**
     * @brief Get all times as a vector.
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
    using typename Base::Duration;
    using typename Base::Time;

    /**
     * @brief Construct a Uniform Time Keeper with start time 0 and interval of 1 second.
     *
     */
    explicit UniformTimeKeeper();

    /**
     * @brief Construct a new Uniform Time Keeper.
     *
     * @param first_
     * @param interval_
     */
    explicit UniformTimeKeeper(const Time first_, const Duration interval_);

    /**
     * @brief Set the stored start time.
     *
     * @param time_
     */
    void change_start_time(const Time time_) override;

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
     * @brief Check if `time_` exists. Otherwise, throw an exception.
     *
     * @param time_
     */
    void require_time(const Time time_) override;

    /**
     * @brief Check if `time_` exists or is between two times. Otherwise, throw an exception.
     *
     * @param time_
     */
    void require_time_within(const Time time_) override;

    /**
     * @brief Get the start time as the stored time.
     *
     * @return Time
     */
    Time start() const override;

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
    Time time(const int index) const override;

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
