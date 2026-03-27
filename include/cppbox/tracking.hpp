#ifndef CPPBOX_TRACKING_HPP
#define CPPBOX_TRACKING_HPP

#include <ranges>
#include <string>
#include <unordered_map>

#include "cppbox/temporal_vector.hpp"
#include "cppbox/time.hpp"

namespace cppbox {

/**
 * @brief Tracking elements (monotonically) over time, storing elements when they change and temporal information about
 * these changes.
 *
 * @tparam Element_
 * @tparam Time_
 */
template<typename Element_, IsTimePoint Time_>
class Tracking {
public:
    using Element = Element_;
    using Time = Time_;

    /**
     * @brief Initialise tracking.
     *
     */
    explicit Tracking() = default;

    /**
     * @brief Initialise tracking (with first update).
     *
     * @param update_time
     * @param element
     */
    explicit Tracking(const Time update_time, const Element& element);

    /**
     * @brief Check if any updates received.
     *
     * @return true
     * @return false
     */
    bool empty() const;

    /**
     * @brief Element at or before a query time.
     *
     * If the update time is also needed, use the `const Element& at(const Time, Time&) const` overload.
     *
     * @param time query time
     * @return const Element&
     */
    const Element& at(const Time time) const;

    /**
     * @brief Element at or before a query time.
     *
     * @param time query time
     * @param update_time the time of the update
     * @return const Element&
     */
    const Element& at(const Time time, Time& update_time) const;

    /**
     * @brief Get the update time corresponding to a query time.
     *
     * If the Element is also needed, use the `const Element& at(const Time, Time&) const` overload.
     *
     * @param time
     * @return Time
     */
    Time at_time(const Time time) const;

    /**
     * @brief Earliest time when tracking was equal to the last element (without the element changing)
     *
     * @return Time
     */
    Time equal_since_time() const;

    /**
     * @brief Check if tracking information is available at a query time.
     *
     * @param time
     * @return true if there exists an element before `time`
     * @return false otherwise
     */
    bool has_tracking_at(const Time time) const;

    /**
     * @brief Last element when tracking was updated
     *
     * @return const Element&
     */
    const Element& last() const;

    /**
     * @brief Last time when tracking was updated
     *
     * @return Time
     */
    Time last_time() const;

    /**
     * @brief Update tracking information, which must be more recent than the last update.
     *
     * @param update_time
     * @param element
     */
    void update(const Time update_time, const Element& element);

private:
    /**
     * @brief Get the index in the tracking at or before a query time.
     *
     * @param time
     * @return int
     */
    int get_index(const Time time) const;

    /**
     * @brief Elements are stored as an ordered temporal vector.
     *
     */
    OrderedTemporalVector<Element, Time> tracking;
};

template<typename Time>
using BinaryTracking = Tracking<bool, Time>;

template<typename Element_, IsTimePoint Time_>
class MultiTracking {
public:
    using Element = Element_;
    using Time = Time_;

    explicit MultiTracking();

    /**
     * @brief Check if any tracking exists, equivalent to `size() == 0`.
     *
     * @return true
     * @return false
     */
    bool empty() const;

    /**
     * @brief Get number of trackings.
     *
     * @return std::size_
     */
    std::size_t size() const;

    /**
     * @brief Check if tracking exists.
     *
     * @param key
     * @return true
     * @return false
     */
    bool has_tracking(const std::string& key) const;

    /**
     * @brief Get trackings.
     *
     * @return const std::unordered_map<std::string, Tracking<Element, Time>>&
     */
    const std::unordered_map<std::string, Tracking<Element, Time>>& trackings() const;

    /**
     * @brief Get tracking.
     *
     * @param key
     * @return const Tracking<Element, Time>&
     */
    const Tracking<Element, Time>& tracking(const std::string& key) const;

    /**
     * @brief Update trackings. If a new key is found, a new tracking is created. If the keys exist, the existing
     * trackings are updated. Not all stored trackings need to be updated when calling this function, and in that case
     * the trackings are no longer synchronised.
     *
     * @param update_time
     * @param elements
     */
    void update(const Time update_time, const std::unordered_map<std::string, Element>& elements);

    /**
     * @brief Update tracking. If the key is new, a new tracking is created. If the key exists, the existing tracking is
     * updated. Synchronicity of the trackings is updated.
     *
     * @param update_time
     * @param key
     * @param element
     */
    void update(const Time update_time, const std::string& key, const Element& element);

    /**
     * @brief Check if all trackings are updated to the same time, i.e. they share the same last update time.
     *
     * @return true if trackings are synchronised or if there are no trackings
     * @return false otherwise
     */
    bool is_synchronised() const;

    /**
     * @brief Check if all trackings are updated to `time`, i.e. they all share `time` as the same last update time.
     *
     * @param time
     * @return true if trackings are synchronised to `time`
     * @return false otherwise or if there are no trackings
     */
    bool is_synchronised_to(const Time time) const;

    /**
     * @brief Get the time to which all trackings are updated.
     *
     * Throws an exception if not synchronised or there are no trackings.
     *
     * @return Time
     */
    Time synchronisation_time() const;

private:
    /**
     * @brief Create or update tracking.
     *
     * @param update_time
     * @param key
     * @param element
     */
    void create_or_update(const Time update_time, const std::string& key, const Element& element);

    /**
     * @brief Check if trackings are synchronised to `time` by checking their last times.
     *
     * @param time
     * @return true
     * @return false
     */
    bool check_if_synchronised_to(const Time time) const;

    /**
     * @brief Trackings by key.
     *
     */
    std::unordered_map<std::string, Tracking<Element, Time>> trackings_;

    /**
     * @brief Flag indicating if trackings are all updated to the same time.
     *
     */
    bool is_synchronised_;
};

template<typename Time>
using BinaryMultiTracking = MultiTracking<bool, Time>;

}

#include "cppbox/impl/tracking.hpp"

#endif
