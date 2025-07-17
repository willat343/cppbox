#ifndef CPPBOX_TIME_HPP
#define CPPBOX_TIME_HPP

#include <chrono>
#include <vector>

namespace cppbox {

/**
 * @brief False version of type trait to check if type is a `std::chrono::Duration<Rep, Period>`.
 *
 * @tparam T type
 */
template<typename T>
struct is_duration : std::false_type {};

/**
 * @brief True version of type trait to check if type is a `std::chrono::Duration<Rep, Period>`.
 *
 * @tparam Rep
 * @tparam Period
 */
template<class Rep, class Period>
struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

/**
 * @brief Value for type trait to check if type is a `std::chrono::Duration<Rep, Period>`.
 *
 * @tparam T type
 */
template<typename T>
constexpr bool is_duration_v = is_duration<T>::value;

/**
 * @brief Duration concept.
 * 
 * @tparam T 
 */
template<typename T>
concept IsDuration = is_duration_v<T>;

/**
 * @brief False version of type trait to check if type is a `std::chrono::time_point<Clock, Duration>`.
 *
 * @tparam T type
 */
template<typename T>
struct is_time_point : std::false_type {};

/**
 * @brief True version of type trait to check if type is a `std::chrono::time_point<Clock, Duration>`.
 *
 * @tparam Clock
 * @tparam Duration
 */
template<class Clock, class Duration>
struct is_time_point<std::chrono::time_point<Clock, Duration>> : std::true_type {};

/**
 * @brief Value for type trait to check if type is a `std::chrono::time_point<Clock, Duration>`.
 *
 * @tparam T type
 */
template<typename T>
constexpr bool is_time_point_v = is_time_point<T>::value;

/**
 * @brief Time point concept.
 * 
 * @tparam T 
 */
template<typename T>
concept IsTimePoint = is_time_point_v<T>;

/**
 * @brief Value for type trait to check if type is a `std::chrono::time_point<Clock, Duration>`.
 *
 * @tparam T type
 */
template<typename T>
constexpr bool is_time_point_or_duration_v = is_time_point_v<T> || is_duration_v<T>;

/**
 * @brief Time point or duration concept.
 * 
 * @tparam T 
 */
template<typename T>
concept IsTimePointOrDuration = is_time_point_or_duration_v<T>;

/**
 * @brief Convert seconds to duration.
 *
 * @tparam Duration type satisfying `std::is_arithemetic_v` or `is_duration_v`
 * @tparam Scalar
 * @param seconds
 * @return Duration
 */
template<class Duration, typename Scalar = double>
    requires(std::is_arithmetic_v<Duration> || is_duration_v<Duration>)
constexpr Duration to_duration(const Scalar seconds);

/**
 * @brief Convert time (since clock epoch) or duration to scalar seconds.
 *
 * @tparam Scalar default double allows use of function without specifying template parameters
 * @tparam TimeOrDuration type satisfying `std::is_arithemetic_v`, `is_time_point_or_duration_v`
 * @param time_or_duration
 * @return Scalar
 */
template<typename Scalar = double, class TimeOrDuration = Scalar>
    requires(std::is_arithmetic_v<TimeOrDuration> || is_time_point_or_duration_v<TimeOrDuration>)
constexpr Scalar to_sec(const TimeOrDuration& time_or_duration);

/**
 * @brief Convert times (since clock epoch) or durations to scalar seconds.
 *
 * @tparam Scalar
 * @tparam TimeOrDuration
 * @param times_or_durations
 * @return std::vector<Scalar>
 */
template<typename Scalar = double, class TimeOrDuration = Scalar>
    requires(std::is_arithmetic_v<TimeOrDuration> || is_time_point_or_duration_v<TimeOrDuration>)
std::vector<Scalar> to_secs(const std::vector<TimeOrDuration>& times_or_durations);

/**
 * @brief Convert seconds to time (since clock epoch).
 *
 * @tparam Time type satisfying `std::is_arithemetic_v` or `is_time_point_v`
 * @tparam Scalar
 * @param seconds
 * @return Time
 */
template<class Time, typename Scalar = double>
    requires(std::is_arithmetic_v<Time> || is_time_point_v<Time>)
constexpr Time to_time(const Scalar seconds);

}

#include "cppbox/impl/time.hpp"

#endif
